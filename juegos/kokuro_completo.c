/*
    Prototipo para el juego de Kokuro
    genera un tablero y el usuario debe llenarlo
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// dimensiones del tablero DIM x DIM (max 9)
#define DIM 6
// la fila 0 y columna 0 se usan para sumas
#define SIZE DIM + 1

typedef struct {
    int valor;     // valor de la celda, 0 si negra
    int sumfila;   // suma de la fila si negra
    int sumcol;    // suma de la columna si negra
} celda_t;

// Función para calcular las sumas de cada bloque
// Recorre cada fila/columna hacia atrás para identificar bloques y calcular sus sumas
void calcular_sumas(celda_t board[][SIZE]) {
    for (int i = 1; i <= DIM; i++) {
        // sumas por filas
        int suma_fila = 0;
        for (int j = DIM; j >= 0; j--) {
            if (board[i][j].valor != 0) {
                suma_fila += board[i][j].valor;
            } else if (suma_fila > 0) {
                board[i][j].sumfila = suma_fila;
                suma_fila = 0;
            }
        }
        // sumas por columnas
        int suma_col = 0;
        for (int j = DIM; j >= 0; j--) {
            if (board[j][i].valor != 0) {
                suma_col += board[j][i].valor;
            } else if (suma_col > 0) {
                board[j][i].sumcol = suma_col;
                suma_col = 0;      
            }
        }
    }
}


// Función para calcular pistas de una línea (fila o columna)
void imprimir_pistas_fila(celda_t arr[SIZE]) {
    for (int i = 0; i < SIZE; i++) 
        if (arr[i].valor == 0 && arr[i].sumfila > 0) 
            printf("%d ", arr[i].sumfila);
    printf("\t");
}


// Función para imprimir pistas de columnas
void imprimir_pistas_columnas(celda_t board[][SIZE]) {
    printf("Sumas columnas:\n");
    for (int j = 1; j < SIZE; j++) {
        printf("C%d: ", j);
        for (int i = 0; i < SIZE; i++) 
        if (board[i][j].valor == 0 && board[i][j].sumcol > 0) 
            printf("%d ", board[i][j].sumcol);
        printf(" | ");
    }
    printf("\n\n");
}


void print(celda_t board[][SIZE]) {
    // sumas de las columnas
    imprimir_pistas_columnas(board);
    // filas con sumas
    for (int i = 1; i < SIZE; i++) {
        imprimir_pistas_fila(board[i]);
        for (int j = 1; j < SIZE; j++) {
            printf("%3c", board[i][j].valor == 0 ? ' ' : board[i][j].valor+'0');
        }
        printf("\n");
    }
    printf("\n");
}


// desordenar usando yates
void permutar(int arr[]) {
    for (int i = 8; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int repetido(celda_t board[][SIZE], int row, int col) {
    int val = board[row][col].valor;
    if (val == 0) return 0; // celda negra no cuenta
    for (int i = 0; i < SIZE; i++) {
        if (i != row && board[i][col].valor == val) {
            return 1; // repetido en la columna
        }
    }
    return 0;
}


void genera_tablero(celda_t board[][SIZE]) {
    srand(time(NULL));
    // sustituir celdas repetidas el columnas por negras (ceros)
    int perm[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 1; i < SIZE; i++) {
        permutar(perm);
        for (int j = 1; j < SIZE; j++)
            printf("%d ", perm[j-1]);
        printf("\n");
        for (int j = 1; j < SIZE; j++) {
            board[i][j] = (celda_t){perm[j-1], 0, 0};
        }
        board[i][0] = (celda_t){0, 0, 0};
        board[0][i] = (celda_t){0, 0, 0};
    }
    // poner a cero las celdas repetidas en columnas
    // me sirven además como celdas vacias
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE; i++) {
            if (repetido(board, i, j)) {
                board[i][j] = (celda_t){0, 0, 0};
            }
        }
    }
    
}

// me gusta como ejercicio, obligando a hacerlo solo con dos bucles anidados
// la version con los dos arrays extra filas/columnas
void sumas(celda_t board[][SIZE]) {
    for (int i = 1; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            board[i][0].sumfila += board[i][j].valor;
            board[0][j].sumcol += board[i][j].valor;
        }
    }
}


int main() {
    celda_t board[SIZE][SIZE];
    genera_tablero(board);
    calcular_sumas(board);
    print(board);
    // TODO: programar la resolucion
    return 0;
}