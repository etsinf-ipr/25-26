/*
Ampliación combinada Carta A + D
- Calles aleatorias (A)
- Giro en cruces (D)
Un solo coche circula por un mapa con 2 calles horizontales y 2 verticales aleatorias.
Al llegar a un cruce, puede girar a la izquierda, derecha o seguir recto.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define N 10    
#define TURNOS 20
#define OUT    999  
#define VACIO      '.'
#define CARRETERAH '-'
#define CARRETERAV '|'
#define CRUCE      '+'
#define COCHE      'o'

// Estructura básica para un coche
enum DIRECTION { ARRIBA, DERECHA, ABAJO, IZQUIERDA };
typedef struct _coche{
    int fila;
    int col;
    int dir; // 0=arriba, 1=derecha, 2=abajo, 3=izquierda
} Coche;

typedef struct {
    int filas_h[2];
    int cols_v[2];
} Calles;

// Prototipos
void inicializar_mapa(char mapa[][N], Calles *calles);
void imprimir_mapa(char mapa[][N]);
void mover_coche(char mapa[][N], Coche *coche);
void restaurar_mapa(char mapa[][N], char mapa_base[][N]);
void nuevo_coche(Coche *coche, Calles *calles);
void situar_coche(char mapa[][N], Coche *coche);
bool dentro_mapa(int fila, int col);
void generar_calles(Calles *calles);
char tipo_carretera(int i, int j, Calles *calles);
void decidir_giro_cruce(char mapa[][N], Coche *coche); // D

int main() {
    char mapa[N][N];
    char mapa_base[N][N];
    Coche coche;
    Calles calles;

    srand(time(NULL));
    generar_calles(&calles);
    inicializar_mapa(mapa_base, &calles);
    nuevo_coche(&coche, &calles);
    
    for (int turno = 0; turno < TURNOS; turno++) {
        restaurar_mapa(mapa, mapa_base);
        mover_coche(mapa, &coche);
        situar_coche(mapa, &coche);
        imprimir_mapa(mapa);
    }
    return 0;
}

// ---------------------------------
// Funciones de CALLES ALEATORIAS (A)
// ---------------------------------
void generar_calles(Calles *calles) {
    calles->filas_h[0] = 1 + rand() % ((N/2) - 1);
    calles->cols_v[0] = 1 + rand() % ((N/2) - 1);
    calles->filas_h[1] = (N/2) + 1 + rand() % (N - (N/2) - 2);
    calles->cols_v[1] = (N/2) + 1 + rand() % (N - (N/2) - 2);
}

char tipo_carretera(int i, int j, Calles *calles) {
    int es_h = (i == calles->filas_h[0] || i == calles->filas_h[1]);
    int es_v = (j == calles->cols_v[0] || j == calles->cols_v[1]);
    if (es_h && es_v) return CRUCE;
    if (es_h) return CARRETERAH;
    if (es_v) return CARRETERAV;
    return VACIO;
}

void inicializar_mapa(char mapa[][N], Calles *calles) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mapa[i][j] = tipo_carretera(i, j, calles);
}

void restaurar_mapa(char mapa[][N], char mapa_base[][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mapa[i][j] = mapa_base[i][j];
}

void imprimir_mapa(char mapa[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c", mapa[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

inline bool dentro_mapa(int fila, int col) {
    return (fila >= 0 && fila < N && col >= 0 && col < N);
}

// ---------------------------------
// Funciones de COCHE
// ---------------------------------
void nuevo_coche(Coche *coche, Calles *calles) {
    int filas[8], cols[8], dirs[8], k = 0;
    for (int i = 0; i < 2; i++) {
        filas[k] = calles->filas_h[i]; cols[k] = 0;    dirs[k++] = DERECHA;
        filas[k] = calles->filas_h[i]; cols[k] = N-1;  dirs[k++] = IZQUIERDA;
    }
    for (int i = 0; i < 2; i++) {
        filas[k] = 0;    cols[k] = calles->cols_v[i]; dirs[k++] = ABAJO;
        filas[k] = N-1;  cols[k] = calles->cols_v[i]; dirs[k++] = ARRIBA;
    }
    int extremo = rand() % 8;
    coche->fila = filas[extremo];
    coche->col  = cols[extremo];
    coche->dir  = dirs[extremo];
}

void situar_coche(char mapa[][N], Coche *coche) {
    if(dentro_mapa(coche->fila, coche->col)) {
        mapa[coche->fila][coche->col] = COCHE;
    }
}

// ---------------------------------
// Ampliación D: Giro en intersecciones (cruces)
// ---------------------------------
void decidir_giro_cruce(char mapa[][N], Coche *coche) {
    if (dentro_mapa(coche->fila, coche->col) && mapa[coche->fila][coche->col] == CRUCE) {
        int giro = rand() % 3; // 0=recto, 1=izquierda, 2=derecha
        if (giro == 1) coche->dir = (coche->dir + 3) % 4;
        else if (giro == 2) coche->dir = (coche->dir + 1) % 4;
    }
}

void mover_coche(char mapa[][N], Coche *coche) {
    int df[] = {-1, 0, 1,  0};
    int dc[] = { 0, 1, 0, -1};
    if(coche->fila == OUT && coche->col == OUT) return;
    decidir_giro_cruce(mapa, coche); // D
    coche->fila += df[coche->dir];
    coche->col  += dc[coche->dir];
    if(dentro_mapa(coche->fila, coche->col) == false) {
        coche->fila = OUT;
        coche->col = OUT;
    }
}
