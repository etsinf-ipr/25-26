/* 
Construye un programa en C que simule los movimientos de un robot. 
La posición del robot será un par de coordenadas (fila,columna) enteras.
Los movimientos permitidos son girar y avanzar una casilla, 
moviéndose a cualquiera de las 4 adyacentes.

usa una estructura para guardar la información del robot
implementa girar y avanzar como funciones
implementa un movimiento aleatorio

Variación: marca en la matriz el camino recorrido y muéstralo 
cuando termine de dar los pasos
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>   

// esto es equivalente a #define NORTE 0 ...
enum direccion {NORTE, ESTE, SUR, OESTE, NUM_DIRECCIONES};
#define NUM_MOVIMIENTOS 1000
#define SIZE 50 

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
    // si llega a un extremo, aparece por el otro
    // fila = -1 -> fila = 49, fila = 50 -> fila = 0

    switch (r->direccion) {
        case NORTE:
            r->fila = (r->fila - 1 + SIZE) % SIZE;
            break;
        case SUR:
            r->fila = (r->fila + 1) % SIZE ;
            break;
        case ESTE:
            r->col =  (r->col + 1) % SIZE;
            break;
        case OESTE:
            r->col = (r->col - 1 + SIZE) % SIZE;
            break;
    }
}

void borrar (int m[][SIZE]){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++)
            m[i][j] = 0;
    }
}

void marcar (int m[][SIZE], int i, int j){
    m[i][j] = 1;
}

void mostrar (int m[][SIZE]) {
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if (m[i][j] == 0)
                printf(" ");
            else
                printf("*");
        }
        printf("\n");
    }
}

int main() {
    struct robot r = {SIZE/2, SIZE/2, NORTE}; // posición inicial (25,25) mirando al NORTE
    int mapa[SIZE][SIZE];
    // comenta la semilla para generar siempre el mismo recorrido
    // (para validar)
    srand(time(NULL)); 
    
    borrar(mapa);
    marcar(mapa, SIZE/2, SIZE/2);

    for (int i = 0; i < NUM_MOVIMIENTOS; i++) { 
        girar(&r);
        avanzar(&r);
        marcar(mapa, r.fila, r.col);
    }
    mostrar(mapa);

    return 0;
}