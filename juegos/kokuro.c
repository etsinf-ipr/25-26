/*
    Prototipo para el juego de Kokuro
    genera un tablero y el usuario debe llenarlo
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// dimensiones del tablero DIM x DIM
#define DIM 6
// la fila 0 y columna 0 se usan para sumas
#define SIZE DIM + 1

typedef struct {
    int valor;     // valor de la celda, 0 si negra
    int sumfila;   // suma de la fila si negra
    int sumcol;    // suma de la columna si negra
} celda_t;


// Función para calcular pistas de una línea (fila o columna)
void calcular_pistas(int arr[DIM], int pistas[DIM], int *num_pistas) {
    int count = 0;
    *num_pistas = 0;
    for (int i = 0; i < DIM; i++) {
        if (arr[i] == 1) {
            count++;
        } else {
            if (count > 0) {
                pistas[(*num_pistas)++] = count;
                count = 0;
            }
        }
    }
    if (count > 0) {
        pistas[(*num_pistas)++] = count;
    }
}

// Función para imprimir pistas de columnas
void imprimir_pistas_columnas(int solucion[][DIM]) {
    printf("Pistas columnas:\n");
    for (int j = 0; j < DIM; j++) {
        int col_arr[DIM], pistas_col[DIM], num_pistas;
        for (int i = 0; i < DIM; i++) col_arr[i] = solucion[i][j];
        calcular_pistas(col_arr, pistas_col, &num_pistas);

        printf("C%d: ", j + 1);
        for (int k = 0; k < num_pistas; k++) printf("%d ", pistas_col[k]);
        if (j != N - 1) printf("| ");
    }
    printf("\n\n");
}


void print(celda_t board[][SIZE]) {
    // sumas de las columnas
    imprimir_pistas_columnas(solucion);
    printf("\n");
    for (int i = 1; i < SIZE; i++) {
        printf("%3d", board[i][0].sumfila);
        for (int j = 1; j < SIZE; j++) {
            printf("%3c", board[i][j].valor == 0 ? ' ' : board[i][j].valor+'0');
        }
        printf("\n");
    }
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
    // TODO: permutaciones por filas
    // sustituir celdas repetidas el columnas por negras (ceros)
    int perm[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 1; i < SIZE; i++) {
        permutar(perm);
        for (int j = 1; j < SIZE; j++)
            printf("%d ", perm[j-1]);
        printf("\n");
        for (int j = 1; j < SIZE; j++) {
            board[i][j].valor = perm[j-1];
        }
        board[i][0].sumfila = 0;
        board[0][i].sumcol = 0;
    }
    print(board);
    // poner a cero las celdas repetidas en columnas
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE; i++) {
            if (repetido(board, i, j)) {
                board[i][j].valor = 0; // celda negra
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
    print(board);
    sumas(board);
    print(board);
    // Aquí se podría agregar la lógica para que el usuario llene el tablero
    return 0;
}