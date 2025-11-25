/*
5. (Opcional) Destapa todas las casillas posibles
ATENCIÓN: Este punto es solo para quienes ya tengan experiencia
programando, porque hacen falta conceptos que se verán en el segundo
semestre en la asignatura Programación (PRG).
Haz que cuando se descubre una casilla vacía (sin ninguna mina alrededor) 
se descubran todas las casillas posibles.

Versión simple: destapa solo las casillas vacías
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
        int fila = rand() % (SIZE - 2) + 1;
        int columna = rand() % (SIZE - 2) + 1;
        if (tablero[fila][columna] != MINA) {
            tablero[fila][columna] = MINA;
            num_minas--;
            añadir_pistas(tablero, fila, columna);
        }
    }
}

void imprimir_tablero(int tablero[][SIZE], bool tapadas[][SIZE]) {
    printf("\n   ");
    for (int j = 1; j < SIZE - 1; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    for (int i = 1; i < SIZE - 1; i++) {
        printf("%2d ", i);
        for (int j = 1; j < SIZE - 1; j++) {
            if (tapadas[i][j]) {
                printf(" · ");
            } else if (tablero[i][j] == MINA) {
                printf(" * ");
            } else if (tablero[i][j] == 0) {
                printf("   ");
            } else {
                printf("%2d ", tablero[i][j]);
            }
        }
        printf("\n");
    }
}


void destapar_celda(int tablero[][SIZE], bool tapadas[][SIZE], int fila, int columna) {
    if (fila < 1 || fila >= SIZE - 1 || columna < 1 || columna >= SIZE - 1 || !tapadas[fila][columna]) {
        return;
    }
    tapadas[fila][columna] = false; // Destapar ANTES de recursión
    destapar_celda(tablero, tapadas, fila-1, columna);
    destapar_celda(tablero, tapadas, fila+1, columna);
    destapar_celda(tablero, tapadas, fila, columna-1);
    destapar_celda(tablero, tapadas, fila, columna+1);
}


void jugar(int tablero[][SIZE], bool tapadas[][SIZE]) {
    int fila, columna;
    bool fin = false;
    
    while (!fin) {
        imprimir_tablero(tablero, tapadas);
        printf("\nIntroduce fila y columna: ");
        scanf("%d %d", &fila, &columna);
        
        if (fila == 0 && columna == 0) {
            printf("Saliendo del juego...\n");
            fin = true;
        } else if (tablero[fila][columna] == MINA){
            printf("¡Has perdido!\n");
            bool vertodo[SIZE][SIZE] = {false};
            imprimir_tablero(tablero, vertodo);
            fin = true;
        } else {
            destapar_celda(tablero, tapadas, fila, columna);
        }
    }
}

int main() {
    int tablero[SIZE][SIZE];
    bool tapadas[SIZE][SIZE];
    
    srand(time(NULL));
    
    inicializar_tablero(tablero);
    inicializar_tapadas(tapadas);
    colocar_minas(tablero, 10);
    
    printf("=== BUSCAMINAS (con expansión automática - versión simple) ===\n");
    printf("Introduce las coordenadas (fila columna) para destapar una celda.\n");
    printf("Introduce 0 0 para salir.\n");
    jugar(tablero, tapadas);
    
    return 0;
}
