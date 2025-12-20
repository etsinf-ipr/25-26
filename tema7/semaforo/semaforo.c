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
} Semaforo;

int setTemporizador() {
    return T_MIN + rand() % (T_MAX - T_MIN + 1);
}


void imprimirCalleC(Semaforo calle[], int n) {
    printf("\r");  // volver al inicio de la línea

    for (int i = 0; i < n; i++) {
        printf("---");

        switch (calle[i].estado) {
            case ROJO:
                printf(COLOR_ROJO "●" COLOR_RESET);
                break;
            case VERDE:
                printf(COLOR_VERDE "●" COLOR_RESET);
                break;
            default:
                printf("?");
        }
        calle[i].temporizador--;
        if(calle[i].temporizador < 0) {
            calle[i].estado = (calle[i].estado == ROJO) ? VERDE : ROJO;
            calle[i].temporizador = setTemporizador();
        }
    }

    printf("---");
    fflush(stdout);
}



/* Inicialización caótica */
void inicializarSemaforos(Semaforo calle[], int n) {
    for (int i = 0; i < n; i++) {
        calle[i].estado = ROJO;  // todos empiezan en rojo
        calle[i].temporizador = setTemporizador();
    }
}

/* Imprimir la calle en una sola línea */
void imprimirCalle(Semaforo calle[], int n) {
    printf("\r");  // volver al inicio de la línea
    for (int i = 0; i < n; i++) {
        char c;
        switch (calle[i].estado) {
            case ROJO:     c = 'R'; break;
            case VERDE:    c = 'V'; break;
            default:       c = '?';
        }
        printf("[%c:%2d] ", c, calle[i].temporizador--);
        if(calle[i].temporizador < 0) {
            calle[i].estado = (calle[i].estado == ROJO) ? VERDE : ROJO;
            calle[i].temporizador = setTemporizador();
        }
    }
    fflush(stdout);
}

int main() {
    Semaforo calle[NUM_SEMAFOROS];

    srand(time(NULL));

    inicializarSemaforos(calle, NUM_SEMAFOROS);

    /* Bucle principal de simulación (solo visualización por ahora) */
    while (1) {
        imprimirCalleC(calle, NUM_SEMAFOROS);
        usleep(300000);  // 0.3 segundos
    }

    return 0;
}
