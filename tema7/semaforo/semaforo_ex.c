/*
    Solución correspondiente al ejercicios de clase
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>   // para usleep (Linux/macOS)

/* Configuración */
#define NUM_SEM 10


/* Estados posibles */
#define ROJO 'R'
#define VERDE 'V'


// ejercicio 1.1
typedef struct _sem semaforo_t;
struct _sem{
    char estado;         // color actual
    int ciclos;           // tiempo base para el cambio de estado
    int temporizador;   // tiempo restante para el cambio de estado
    int cambio;         // indicador de cambio reciente
};

// ---------------------------
// SEMAFORO
// ---------------------------

// ejercicio 1.2
semaforo_t crear_semaforo() {
    semaforo_t s;
    s.estado = 'R';  // todos empiezan en rojo
    s.ciclos = rand() % 10 + 1;
    s.temporizador = s.ciclos;
    s.cambio = 0;
    return s;
}


// ejercicio 1.3
void step(semaforo_t *s) {
    s->temporizador--;
    s->cambio = 0;
    if (s->temporizador < 0) {
        s->estado = (s->estado == 'R') ? 'V' : 'R';
        s->temporizador = s->ciclos;
        // bonus 3.1
        // if(s->estado == 'V')
        s->cambio = 1;  // marcar cambio
    }
}


// ---------------------------
// CALLE
// ---------------------------


// ejercicio 2.1
void inicializar_semaforos(semaforo_t calle[]) {
    for (int i = 0; i < NUM_SEM; i++) {
        calle[i] = crear_semaforo();
    }
}

// ejercicio 2.2
void run(semaforo_t calle[], int n) {
    for(int c = 0; c < n; c++) {
        printf("\r");  // volver al inicio de la línea
        for (int i = 0; i < NUM_SEM; i++) {
            step(&calle[i]);
            /* si algun vecino ha cambiado me acelero un poco */
            if ((i > 0 && calle[i-1].cambio) ||
                (i < NUM_SEM - 1 && calle[i+1].cambio)) {
                // bonus 3.2
                // if(calle[i].estado == 'R')
                calle[i].ciclos--;
            }
            printf("[%c:%2d] ", calle[i].estado, calle[i].temporizador);
        }
        
        fflush(stdout);
        usleep(300000);  // espera 0.3 segundos
    }
    printf("\n");
}


// ejercicio 2.3
void cambiados(semaforo_t calle[], semaforo_t change[], int *c){
    int j = 0;
    // para la versión en una línea
    //(*c) = 0;
    for(int i = 0; i < NUM_SEM; i++){
        if(calle[i].cambio == 1){
            // en una línea
            //change[(*c)++] = calle[i];
            change[j] = calle[i];
            j++;
        }
    }
    //esto sobra en la versión en una línea
    (*c) = j;
}



// ejercicio 2.4
int main() {
    semaforo_t calle[NUM_SEM];
    srand(time(NULL));
    inicializar_semaforos(calle);
    run(calle, 2000);
    return 0;
}
