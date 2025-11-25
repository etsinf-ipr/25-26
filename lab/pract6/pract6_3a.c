/*
3. Muestra el tablero de juego
Para poder jugar, necesitas otra capa que marque las casillas que has
destapado. Utiliza otra matriz del mismo tamaño con unos y ceros que
indiquen si la celda de esas coordenadas está tapada o destapada.

Opción sencilla: imprime un punto . si la celda está tapada y el valor
numérico si está destapada
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// esta biblioteca permite usar el tipo bool (< C23)
#include <stdbool.h>

#define SIZE 12
#define MINA -1
    
void inicializar_tablero(int tablero[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            tablero[i][j] = 0;
        }
    }
}

void inicializar_tapadas(bool tapadas[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            tapadas[i][j] = true;
        }
    }
}

void añadir_pistas(int tablero[][SIZE], int fila, int columna) {
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
        int fila = rand() % 10 + 1;
        int columna = rand() % 10 + 1;
        if (tablero[fila][columna] != MINA) {
            tablero[fila][columna] = MINA;
            num_minas--;
            añadir_pistas(tablero, fila, columna);
        }
    }
}

void imprimir_tablero(int tablero[][SIZE], bool tapadas[][SIZE]) {
    // Imprimir encabezados de columna
    printf("\n   ");
    for (int j = 1; j <= 10; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    for (int i = 1; i <= 10; i++) {
        printf("%2d ", i); // Encabezado de fila
        for (int j = 1; j <= 10; j++) {
            if (tapadas[i][j]) {
                printf(" . ");
            } else {
                printf("%2d ", tablero[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int tablero[SIZE][SIZE];
    bool tapadas[SIZE][SIZE];
    
    srand(time(NULL));
    
    inicializar_tablero(tablero);
    inicializar_tapadas(tapadas);
    colocar_minas(tablero, 10);
    imprimir_tablero(tablero, tapadas);
    
    // Ejemplo: destapar algunas celdas
    tapadas[3][3] = false;
    tapadas[5][7] = false;
    printf("\nTablero después de destapar (3,3) y (5,7):\n");
    imprimir_tablero(tablero, tapadas);
    
    return 0;
}
