/*
1. Creación del tablero con minas
Crea un tablero de 10 × 10 y añade en él 10 minas en posiciones aleatorias. 
Imprime luego el tablero completo en la pantalla. Se recomienda usar funciones 
para cada operación.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define MINA -1

void inicializar_tablero(int tablero[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            tablero[i][j] = 0;
        }
    }
}

void colocar_minas(int tablero[][SIZE], int num_minas) {
    while (num_minas > 0) {
        int fila = rand() % 10 + 1;    // Entre 1 y 10
        int columna = rand() % 10 + 1; // Entre 1 y 10
        if (tablero[fila][columna] != MINA) {
            tablero[fila][columna] = MINA;
            num_minas--;
        }
    }
}

void imprimir_tablero(int tablero[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%2d ", tablero[i][j]);
        }
        printf("\n");
    }
}


int main() {
    int tablero[SIZE][SIZE];
    
    srand(time(NULL));
    
    inicializar_tablero(tablero);
    colocar_minas(tablero, 10);
    imprimir_tablero(tablero);
    
    return 0;
}
