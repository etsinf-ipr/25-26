/*
    genera un cuadado latino 9x9 y extrae uno n x n
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIM 6

// yates shuffle array de 9 elementos (1..9)
void permutar(int arr[]) {
    for (int i = 8; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// genera un cuadrado latino completo 9x9
void completo(int board[][9]) {
    // fila base {1 2 3 4 5 6 7 8 9}
    for(int i = 0; i < 9; i++)
        board[0][i] = i + 1;
    // resto de filas
    for (int i = 1; i < 9; i++) {
        //copia la fila anterior desplazada 1 posición
        for (int j = 0; j < 9; j++) 
            board[i][j] = board[i-1][(j+1) % 9];    
    }
}


void genera_latino(int lat[][DIM]) {
    srand(time(NULL));
    // generar cuadrado latino completo 9x9
    int board[9][9];
    completo(board);
    // indices de las filas y columnas random a extraer
    int idxf[9] = {0,1,2,3,4,5,6,7,8};
    int idxc[9] = {0,1,2,3,4,5,6,7,8};
    permutar(idxf);
    permutar(idxc);
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            lat[i][j] = board[idxf[i]][idxc[j]];
        }
    }
}

void print(int board[][DIM]) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}


int main() {
    int board[DIM][DIM];
    genera_latino(board);
    print(board);
    return 0;
}