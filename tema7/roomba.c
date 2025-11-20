/* 
Construye un programa en C que simule los movimientos de un robot. 
La posición del robot será un par de coordenadas (fila,columna) enteras.
Los movimientos permitidos son girar y avanzar una casilla, 
moviéndose a cualquiera de las 4 adyacentes.

El programa debe imprimir en pantalla las posiciones en las que se encuentra 
el robot en cada instante de tiempo, una en cada línea, separadas por comas

usa una estructura para guardar la información del robot
implementa girar y avanzar como funciones
implementa un movimiento aleatorio
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>   

// esto es equivalente a #define NORTE 0 ...
enum direccion {NORTE, ESTE, SUR, OESTE, NUM_DIRECCIONES};
#define NUM_MOVIMIENTOS 100

struct robot {
    int fila;
    int col;
    int direccion; // 0:NORTE, 1:ESTE, 2:SUR, 3:OESTE
};

void imprimir_posicion(struct robot r) {
    printf("%d,%d\n", r.fila, r.col);
}

void girar(struct robot *r) {
    r->direccion = rand() % NUM_DIRECCIONES;
}

void avanzar(struct robot *r) {
    switch (r->direccion) {
        case NORTE:
            r->fila -= 1;
            break;
        case SUR:
            r->fila += 1;
            break;
        case ESTE:
            r->col += 1;
            break;
        case OESTE:
            r->col -= 1;
            break;
    }
}

void movimiento_aleatorio(struct robot *r) {
    int accion = rand() % 2; // 0: girar, 1: avanzar
    if (accion == 0) {
        girar(r);
    } else {
        avanzar(r);
    }
}

int main() {
    struct robot r = {25, 25, NORTE}; // posición inicial (25,25    ) mirando al NORTE
    // comenta la semilla para generar siempre el mismo recorrido
    // (para validar)
    srand(time(NULL)); 
    
    for (int i = 0; i < NUM_MOVIMIENTOS; i++) { // realizar 100 movimientos aleatorios
        imprimir_posicion(r);
        girar(&r);
        avanzar(&r);
        // alternativa (descomentar):
        // la opción de girar o avanzar también es aleatoria
        // movimiento_aleatorio(&r);
    }
    imprimir_posicion(r); // imprimir posición final

    return 0;
}