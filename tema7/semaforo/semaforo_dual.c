/*
    prueba de cconcepto
    semáforos en dos calles que se cruzan
    variación sobre el funcionamiento básico (view)

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
    int estado;         // color actual
    int base;           // tiempo base para el cambio de estado
    int temporizador;   // tiempo restante para el cambio de estado
    int cambio;         // indicador de cambio reciente
} semaforo_t;

// ---------------------------
// SEMAFORO
// ---------------------------


int set_base() {
    return T_MIN + rand() % (T_MAX - T_MIN + 1);
}


void ajusta_base(semaforo_t *s, float factor) {
    s->base = (int)(s->base * factor);
    if (s->base < T_MIN) s->base = T_MIN;
}


semaforo_t crear_semaforo() {
    semaforo_t s;
    s.estado = ROJO;  // todos empiezan en rojo
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
        s->cambio = 1;  // marcar cambio
    }
}


// ---------------------------
// CALLE
// ---------------------------



/* Ajustar el semáforo con los vecinos */
void ajustar(semaforo_t calle[], int i) {
    step(&calle[i]);
    /* si algun vecino ha cambiado me acelero un poco */
    if ((i > 0 && calle[i - 1].cambio) ||
        (i < NUM_SEMAFOROS - 1 && calle[i + 1].cambio)) {
        ajusta_base(&calle[i], 0.9);  // acelerar un 10%
    }
}

/* Inicialización caótica */
void inicializar_semaforos(semaforo_t calle[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        calle[i] = crear_semaforo();
    }
}


void imprimir_vertical_parcial(semaforo_t calle_v[], int inicio, int fin, int cruce, int ancho_h) {
    printf("%*s", 4 * cruce + 3, "");
    printf("|\n");
    for (int i = inicio; i <= fin; i++) {
        printf("%*s", 4 * cruce+3, "");  // espacios antes del semáforo
        switch (calle_v[i].estado) {
            case ROJO:   printf(COLOR_ROJO "●" COLOR_RESET); break;
            case VERDE:  printf(COLOR_VERDE "●" COLOR_RESET); break;
            default:     printf("?");
        }
        printf("\n");
        printf("%*s", 4 * cruce + 3, "");
        printf("|\n");
    }
}


/* Imprimir la calle en una sola línea con colores */
void imprimir_calleC(semaforo_t calle[], int n) {
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
        ajustar(calle, i);
    }
    printf("---\n");
    fflush(stdout);
}

// Fuerza un semáforo a rojo y reinicia su temporizador
void forzar_rojo(semaforo_t *s) {
    s->estado = ROJO;
    s->temporizador = s->base;
}

// Sincroniza el semáforo de la intersección para que solo uno esté en verde
void sincronizar_cruce(semaforo_t *a, semaforo_t *b) {
    // Prioridad aleatoria en cada ciclo
    if (rand() % 2 == 0) {
        // Prioridad a 'a'
        if (a->estado == VERDE) {
            forzar_rojo(b);
        }
    } else {
        // Prioridad a 'b'
        if (b->estado == VERDE) {
            forzar_rojo(a);
        }
    }
}

int main() {
    semaforo_t calle1[NUM_SEMAFOROS];
    semaforo_t calle2[NUM_SEMAFOROS];
    int cruce = NUM_SEMAFOROS / 2;

    inicializar_semaforos(calle1, NUM_SEMAFOROS);
    inicializar_semaforos(calle2, NUM_SEMAFOROS);

    printf("[Ctrl]+C para salir\n\n");
    while (1) {
        // Limpiar pantalla
        printf("\033[2J\033[H");

        // Actualizar ambas calles
        for (int i = 0; i < NUM_SEMAFOROS; i++) {
            ajustar(calle1, i);
            ajustar(calle2, i);
        }
        // Sincronizar el cruce central
        sincronizar_cruce(&calle1[cruce], &calle2[cruce]);

        // Imprimir vertical antes del cruce
        imprimir_vertical_parcial(calle2, 0, cruce-1, cruce, NUM_SEMAFOROS);
        // Imprimir horizontal
        imprimir_calleC(calle1, NUM_SEMAFOROS);
        // Imprimir vertical después del cruce
        imprimir_vertical_parcial(calle2, cruce+1, NUM_SEMAFOROS-1, cruce, NUM_SEMAFOROS);
        printf("\n");
        usleep(300000);  // 0.3 segundos
    }

    return 0;
}
