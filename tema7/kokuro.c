/*
    Prototipo para el juego de Kokuro
    genera un tablero y el usuario debe llenarlo
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 7

// desordenar usando yates
void permutar(int arr[]) {
    for (int i = 8; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void genera_tablero(int board[][SIZE]) {
    srand(time(NULL));
    // TODO: permnutaciones por filas
    // sustituir celdas repetidas el columnas por negras (ceros)
    int perm[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < SIZE; i++) {
        permutar(perm);
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = perm[j];
        }
    }
    // poner a cero las celdas repetidas en columnas
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE; i++) {
            for (int k = i + 1; k < SIZE; k++) {
                if (board[i][j] == board[k][j]) {
                    board[k][j] = 0;
                }
            }
        }
    }
    
}

// me gusta como ejercicio, obligando a hacerlo solo con dos bucles anidados
void sumas(int board[][SIZE], int filas[], int columnas[]) {
    for (int i = 0; i < SIZE; i++) {
        filas[i] = 0;
        columnas[i] = 0;
        for (int j = 0; j < SIZE; j++) {
            filas[i] += board[i][j];
            columnas[i] += board[j][i];
        }
    }
}


void print(int board[][SIZE], int filas[], int columnas[]) {
    // sumas de las columnas
    printf("   ");
    for(int i = 0; i < SIZE; i++) {
        printf("%3d", columnas[i]);
    }
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%3d", filas[i]);
        for (int j = 0; j < SIZE; j++) {
            printf("%3c", board[i][j] == 0 ? ' ' : board[i][j]+'0');
        }
        printf("\n");
    }
}


int main() {
    int board[SIZE][SIZE];
    int filas[SIZE], columnas[SIZE];
    genera_tablero(board);
    sumas(board, filas, columnas);
    print(board,filas, columnas);
    // Aquí se podría agregar la lógica para que el usuario llene el tablero
    return 0;
}