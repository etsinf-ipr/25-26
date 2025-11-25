/*
2. Añade las pistas
Recorre el tablero anterior rellenando las pistas. Cada casilla debe
contener un número que es la cantidad de minas que hay en las ocho
celdas adyacentes. Sugerencia: para evitar manejar código específico
para los bordes o las esquinas, define un tamaño con un marco de una
casilla alrededor de todo el tablero y déjalo vacío (es decir, crea un
tablero de 12 × 12 y usa las celdas de 1 a 10 ambas inclusive).
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 12
#define MINA -1

void inicializar_tablero(int tablero[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            tablero[i][j] = 0;
        }
    }
}

void añadir_pistas(int tablero[][SIZE], int fila, int columna) {
    // Incrementar las 8 casillas adyacentes
    for (int i = fila-1; i <= fila+1; i++) {
        for (int j = columna-1; j <= columna+1; j++) {
            if (tablero[i][j] != MINA) {
                tablero[i][j]++;
            }
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
            añadir_pistas(tablero, fila, columna);
        }
    }
}

void imprimir_tablero(int tablero[][SIZE]) {
   for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
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
