#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5

// Función para calcular pistas de una línea (fila o columna)
void calcular_pistas(int arr[N], int pistas[N], int *num_pistas) {
    int count = 0;
    *num_pistas = 0;
    for (int i = 0; i < N; i++) {
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

// Función para generar la matriz solución aleatoria
void generar_solucion(int solucion[N][N]) {
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            solucion[i][j] = (rand() % 10 < 6) ? 1 : 0; // 60% probabilidad de 1
        }
    }
}

void imprimir_solucion(int solucion[N][N]) {
    printf("Solución:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", solucion[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Función para imprimir pistas de columnas
void imprimir_pistas_columnas(int solucion[N][N]) {
    printf("Pistas columnas:\n");
    for (int j = 0; j < N; j++) {
        int col_arr[N], pistas_col[N], num_pistas;
        for (int i = 0; i < N; i++) col_arr[i] = solucion[i][j];
        calcular_pistas(col_arr, pistas_col, &num_pistas);

        printf("C%d: ", j + 1);
        for (int k = 0; k < num_pistas; k++) printf("%d ", pistas_col[k]);
        if (j != N - 1) printf("| ");
    }
    printf("\n\n");
}

// Función para imprimir tablero con pistas de filas
void imprimir_tablero(int solucion[N][N], int tablero_usuario[N][N]) {
    imprimir_pistas_columnas(solucion);
    printf("Pistas filas + tablero:\n");
    for (int i = 0; i < N; i++) {
        int pistas_fila[N], num_pistas;
        calcular_pistas(solucion[i], pistas_fila, &num_pistas);
        for (int k = 0; k < num_pistas; k++) printf("%d ", pistas_fila[k]);
        if (num_pistas == 1) printf("  ");
        else if (num_pistas == 0) printf("\t\t");

        for (int j = 0; j < N; j++) {
            printf("%c ", tablero_usuario[i][j] ? '#' : '.');
        }
        printf("\n");
    }
    printf("\n");
}

// Función para pedir jugada al usuario y actualizar el tablero
int pedir_jugada(int tablero_usuario[N][N]) {
    int fila, col;
    printf("Fila: "); scanf("%d", &fila);
    printf("Columna: "); scanf("%d", &col);

    if (fila == 0 && col == 0) return 0; // señal de terminar

    if (fila < 1 || fila > N || col < 1 || col > N) {
        printf("Coordenadas fuera de rango. Intenta de nuevo.\n");
        return 1;
    }

    tablero_usuario[fila - 1][col - 1] = 1;
    return 1;
}

// Función para comprobar si el tablero del usuario coincide con la solución
int comprobar_solucion(int solucion[N][N], int tablero_usuario[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (solucion[i][j] != tablero_usuario[i][j]) return 0;
        }
    }
    return 1;
}

int main() {
    int solucion[N][N];
    int tablero_usuario[N][N] = {0};

    generar_solucion(solucion);

    printf("Introduce coordenadas de las celdas a marcar (fila y columna entre 1 y %d).\n", N);
    printf("Introduce 0 0 para terminar.\n\n");

    while (1) {
        imprimir_tablero(solucion, tablero_usuario);
        if (!pedir_jugada(tablero_usuario)) break;
    }

    imprimir_tablero(solucion, tablero_usuario);

    if (comprobar_solucion(solucion, tablero_usuario))
        printf("¡Felicidades! Has completado correctamente el nonograma.\n");
    else{
        printf("No coincide con la solución. ¡Intenta de nuevo!\n");
        imprimir_solucion(solucion);
    }

    return 0;
}
