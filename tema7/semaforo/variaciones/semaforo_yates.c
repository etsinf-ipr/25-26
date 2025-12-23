/*
    variación sonre fly
    elimina el orden secuencial de activación
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>   // para usleep (Linux/macOS)

/* Configuración */
#define NUM_SEMAFOROS 60
#define T_MIN 1
#define T_MAX 15
#define SEPARADOR ""

/* Estados posibles */
#define ROJO 0
#define VERDE 1
#define AMARILLO 2

#define COLOR_ROJO     "\033[31m"
#define COLOR_VERDE    "\033[32m"
#define COLOR_AMARILLO "\033[33m"
#define COLOR_RESET    "\033[0m"


typedef struct {
    int estado;         // color actual
    float base;           // tiempo base para el cambio de estado
    int temporizador;   // tiempo restante para el cambio de estado
    int cambio;         // indicador de cambio reciente
} semaforo_t;

// ---------------------------
// SEMAFORO
// ---------------------------


float set_base() {
    return T_MIN + rand() % (T_MAX - T_MIN + 1);
}


void ajusta_base(semaforo_t *s, float factor) {
    s->base = s->base + factor;
    //s->base = (int)(s->base * factor);
    if (s->base < T_MIN) s->base = T_MIN;
}


semaforo_t crear_semaforo() {
    semaforo_t s;
    s.estado = ROJO;
    s.base = set_base();
    s.temporizador = s.base;
    s.cambio = 0;
    return s;
}


void step(semaforo_t *s) {
    s->temporizador--;
    s->cambio = 0;
    if (s->temporizador < 0) {
        s->estado = (s->estado == ROJO) ? VERDE : ROJO;
        s->temporizador = s->base;
        // marcar cambio solo en verde
        if (s->estado == VERDE)
            s->cambio = 1;
    }
}


// ---------------------------
// CALLE
// ---------------------------



/* Ajustar el semáforo con los vecinos */
void ajustar(semaforo_t calle[], int i) {
    step(&calle[i]);
    // solo proceso cambios estando en rojo
    if (calle[i].estado == VERDE) return;
    /* si algun vecino ha cambiado me acelero un poco */
    if ((i > 0 && calle[i - 1].cambio) ||
        (i < NUM_SEMAFOROS - 1 && calle[i + 1].cambio)) {
        ajusta_base(&calle[i], -0.5);  
    }
}


/* Inicialización caótica */
void inicializar_semaforos(semaforo_t calle[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        calle[i] = crear_semaforo();
    }
}


void desordenar(int arr[]) {
    for (int i = NUM_SEMAFOROS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Intercambiar arr[i] y arr[j]
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

/* Imprimir la calle en una sola línea con colores */
void imprimir_calleC(semaforo_t calle[], int n) {
    // Genera un orden aleatorio para activar los semáforos
    int orden[NUM_SEMAFOROS];
    for (int i = 0; i < n; i++) orden[i] = i; 
    desordenar(orden);
    printf("\r");  // volver al inicio de la línea
    for (int i = 0; i < NUM_SEMAFOROS; i++) {
        int s = orden[i];
        printf(SEPARADOR);
        switch (calle[s].estado) {
            case ROJO:
                printf(COLOR_ROJO "●" COLOR_RESET);
                break;
            case VERDE:
                printf(COLOR_VERDE "●" COLOR_RESET);
                break;
            default:
                printf("?");
        }
        ajustar(calle, s);
    }
    printf(SEPARADOR);
    fflush(stdout);
}


/* Imprimir la calle en una sola línea */
void imprimir_calle(semaforo_t calle[], int n) {
    printf("\r");  // volver al inicio de la línea
    for (int i = 0; i < n; i++) {
        char c;
        switch (calle[i].estado) {
            case ROJO:     c = 'R'; break;
            case VERDE:    c = 'V'; break;
            default:       c = '?';
        }
        printf("[%c:%2d] ", c, calle[i].temporizador);
        ajustar(calle, i);
    }
    fflush(stdout);
}



int main() {
    semaforo_t calle[NUM_SEMAFOROS];

    inicializar_semaforos(calle, NUM_SEMAFOROS);
    /* Bucle principal de simulación (solo visualización por ahora) */
    printf("[Ctrl]+C para salir\n\n");
    while (1) {
        imprimir_calleC(calle, NUM_SEMAFOROS);
        usleep(300000);  // 0.3 segundos
    }

    return 0;
}
