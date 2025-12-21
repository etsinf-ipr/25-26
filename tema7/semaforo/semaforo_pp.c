/*
    version pretty print: 
    semáforos con dos colores y el temporizador debajo
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>   // para usleep (Linux/macOS)

/* Configuración */
#define NUM_SEMAFOROS 10
#define T_MIN 1
#define T_MAX 10

/* Estados posibles */
#define ROJO 0
#define VERDE 1
#define AMARILLO 2

#define COLOR_ROJO     "\033[31m"
#define COLOR_VERDE    "\033[32m"
#define COLOR_AMARILLO "\033[33m"
#define COLOR_RESET    "\033[0m"


typedef struct {
    int estado;
    int temporizador;
} semaforo_t;


int set_temporizador() {
    return T_MIN + rand() % (T_MAX - T_MIN + 1);
}



void gestionar_temporizador(semaforo_t *s) {
    s->temporizador--;
    if (s->temporizador < 0) {
        s->estado = (s->estado == ROJO) ? VERDE : ROJO;
        s->temporizador = set_temporizador();
    }
}



/* Inicialización caótica */
void inicializar_semaforos(semaforo_t calle[], int n) {
    for (int i = 0; i < n; i++) {
        calle[i].estado = ROJO;  // todos empiezan en rojo
        calle[i].temporizador = set_temporizador();
    }
}


void imprimir_calle_all(semaforo_t calle[], int n) {
    // Limpiar pantalla
    printf("\033[2J\033[H");

    // Primera línea: bolita roja (arriba) con tres espacios entre cada una
    for (int i = 0; i < n; i++) {
        printf("   ");
        if (calle[i].estado == ROJO)
            printf(COLOR_ROJO "●" COLOR_RESET );
        else
            printf(COLOR_ROJO "○" COLOR_RESET );
    }
    printf("\n");

    // Línea de la calle con bolitas verdes intercaladas
    for (int i = 0; i < n; i++) {
        printf("---");
        if (calle[i].estado == VERDE)
            printf(COLOR_VERDE "●" COLOR_RESET);
        else
            printf(COLOR_VERDE "○" COLOR_RESET);
    }
    printf("---\n");

    // Temporizadores alineados con formato %%4d
    for (int i = 0; i < n; i++) {
        printf("%4d", calle[i].temporizador);
    }
    printf("\n");

    // Gestionar temporizadores después de mostrar
    for (int i = 0; i < n; i++) {
        gestionar_temporizador(&calle[i]);
    }
}



int main() {
    semaforo_t calle[NUM_SEMAFOROS];

    srand(time(NULL));

    inicializar_semaforos(calle, NUM_SEMAFOROS);

    /* Bucle principal de simulación (solo visualización por ahora) */
    printf("[Ctrl]+C para salir\n\n");
    while (1) {
        imprimir_calle_all(calle, NUM_SEMAFOROS);
        usleep(300000);  // 0.3 segundos
    }

    return 0;
}
