/*
    procesado de una pieza en una cadena de montaje
    Una estructura para la pieza.
    Un array para marcar el proceso realizado en cada máquina
*/

#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int codigo;        // código de la pieza
    int total;         // duración total del procesado
    char estado;       // C: correcta, D: defectuosa
} pieza_t;


typedef struct {
    int duracion;  // duración de la etapa
    char estado;   // estado de la etapa: P:pendiente, C:correcta, E:error
    int anterior;  // índice de la etapa anterior (-1 si no hay)
} etapa_t;

#define NUM_ETAPAS 5 // número de etapas en la cadena de montaje   


void procesar_etapa(pieza_t *p, etapa_t e){
    p->total += e.duracion;
    if(p->estado != 'D') // si ya está defectuosa, no cambiar
        p->estado = (e.estado == 'C') ? 'C' : 'D';
}


void errores(etapa_t e[], etapa_t error[], int *numerr) {
    int j = 0;
    for (int i = 0; i < NUM_ETAPAS; i++) {
        if (e[i].estado == 'E') {
            error[j] = e[i];
            j++;
        }
    }
    *numerr = j;
}

int siguiente(etapa_t etapas[]) {
    for (int i = 0; i < NUM_ETAPAS; i++) {
        int ant = etapas[i].anterior;
        if (etapas[i].estado == 'P' && 
            (etapas[i].anterior == -1 || etapas[ant].estado == 'C'))
            return i;
    }
    return -1; // no se ha encontrado ninguna etapa disponible
}

int procesar(pieza_t *pieza, etapa_t etapas[]) {
    int completadas = 0;
    while (completadas < NUM_ETAPAS) {
        int sig = siguiente(etapas);
        if (sig == -1) break; // también return completadas;
        // esto no forma parte del examen
        etapas[sig].estado = (rand() % 10 < 7) ? 'C' : 'E'; // 70% de éxito
        //////////////////////////////////
        procesar_etapa(pieza, etapas[sig]);  
        completadas++;
    }
    return completadas;
}

/////////////////////////////////////////
//Esto no forma parte del examen
void setup(etapa_t etapas[]) {
    srand(42); // semilla para reproducibilidad
    // 2->0, 1->3, 0->4
    int dep[NUM_ETAPAS] = {2, -1, -1, 1, 0 };
    for (int i = 0; i < NUM_ETAPAS; i++) {
        etapas[i].duracion = rand() % 10 + 20; // duración entre 20 y 30
        etapas[i].anterior = dep[i];
        etapas[i].estado = 'P'; // pendiente
    }
}
/////////////////////////////////////////

// Ejemplo de uso
int main() {
    etapa_t etapa[NUM_ETAPAS];
    pieza_t pieza = {1234, 0, ' '}; // también estado:'C'

    //esto no forma parte del examen
    setup(etapa); 
    ////////////////////////////////
    procesar(&pieza, etapa);

    etapa_t errores_list[NUM_ETAPAS];
    int num_errores = 0;
    errores(etapa, errores_list, &num_errores);

    printf("Pieza código: %d\n", pieza.codigo);
    printf("Duración total: %d\n", pieza.total);
    printf("Estado final: %c\n", pieza.estado);
    printf("Número de errores: %d\n", num_errores);
    return 0;
}
