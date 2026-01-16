

#include <stdio.h>

typedef struct {
    int valor;        // número del jugador, 0 si vacío
    int sumaFila;     // suma de la fila (solo en casillas negras)
    int sumaCol;      // suma de la columna (solo en casillas negras)
    int esNegra;      // 1 = casilla negra, 0 = casilla blanca
} Celda;

#define FIL 3
#define COL 3

Celda tablero[FIL][COL];


void inicializarTablero() {
    // Primera fila
    tablero[0][0] = (Celda){0, 0, 0, 1};  // esquina superior
    tablero[0][1] = (Celda){0, 0, 4, 1};  // suma columna 1
    tablero[0][2] = (Celda){0, 0, 3, 1};  // suma columna 2

    // Segunda fila
    tablero[1][0] = (Celda){0, 3, 0, 1};  // suma fila 1
    tablero[1][1] = (Celda){0, 0, 0, 0};  // casilla blanca
    tablero[1][2] = (Celda){0, 0, 0, 0};  // casilla blanca

    // Tercera fila
    tablero[2][0] = (Celda){0, 4, 0, 1};  // suma fila 2
    tablero[2][1] = (Celda){0, 0, 0, 0};  // casilla blanca
    tablero[2][2] = (Celda){0, 0, 0, 0};  // casilla blanca
}

void mostrarTablero() {
    for(int i=0; i<FIL; i++) {
        for(int j=0; j<COL; j++) {
            if(tablero[i][j].esNegra) {
                if(tablero[i][j].sumaFila && tablero[i][j].sumaCol)
                    printf("%d\\%d ", tablero[i][j].sumaFila, tablero[i][j].sumaCol);
                else if(tablero[i][j].sumaFila)
                    printf("%d\\  ", tablero[i][j].sumaFila);
                else if(tablero[i][j].sumaCol)
                    printf(" \\%d ", tablero[i][j].sumaCol);
                else
                    printf("    ");
            } else {
                if(tablero[i][j].valor)
                    printf(" %d ", tablero[i][j].valor);
                else
                    printf(" . ");
            }
        }
        printf("\n");
    }
}

int esValido(int fila, int col, int num) {
    // revisar fila
    int sumaFila = 0;
    for(int j=1; j<COL; j++) {
        if(tablero[fila][j].valor == num) return 0; // repetido
        sumaFila += tablero[fila][j].valor;
    }
    if(sumaFila + num > tablero[fila][0].sumaFila) return 0;

    // revisar columna
    int sumaCol = 0;
    for(int i=1; i<FIL; i++) {
        if(tablero[i][col].valor == num) return 0; // repetido
        sumaCol += tablero[i][col].valor;
    }
    if(sumaCol + num > tablero[0][col].sumaCol) return 0;

    return 1;
}

int juegoTerminado() {
    for(int i=1;i<FIL;i++)
        for(int j=1;j<COL;j++)
            if(tablero[i][j].valor == 0)
                return 0;
    return 1;
}

void jugar() {
    int fila, col, num;
    while(!juegoTerminado()) {
        mostrarTablero();
        printf("Ingresa fila y columna (1-2) y numero: ");
        scanf("%d %d %d", &fila, &col, &num);
        if(esValido(fila, col, num))
            tablero[fila][col].valor = num;
        else
            printf("Movimiento inválido!\n");
    }
    mostrarTablero();
    printf("¡Kakuro completado!\n");
}

int main() {
    inicializarTablero();
    jugar();
    return 0;
}