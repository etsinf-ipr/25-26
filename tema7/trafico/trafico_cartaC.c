/*
Ampliación Carta C – Múltiples coches
Mantener un array de coches.
Se mueven por turnos.
No pueden ocupar la misma celda
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define N 10    
#define TURNOS 20
#define OUT    999  
#define MAX_COCHES 5    // número máximo de coches a generar
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

// Prototipos de funciones
void inicializar_mapa(char mapa[][N]);
void imprimir_mapa(char mapa[][N]);
void mover_coche(char mapa[][N], Coche *coche, Coche coches[]);
// funciones añadidas
void restaurar_mapa(char mapa[][N], char mapa_base[][N]); 
void nuevo_coche(Coche *coche);
void situar_coche(char mapa[][N], Coche *coche);
bool dentro_mapa(int fila, int col);
// funciones para la ampliación: múltiples coches
void inicializar_coches(Coche coches[]);
void situar_coches(char mapa[][N], Coche coches[]);
void mover_coches(char mapa[][N], Coche coches[]);
bool celda_ocupada(int fila, int col, int dir, Coche coches[], Coche *coche_actual);
bool direcciones_opuestas(int dir1, int dir2);

int main() {
    char mapa[N][N];       // mapa actual con coches
    char mapa_base[N][N];  // mapa base para restaurar cada turno
    Coche coches[MAX_COCHES];

    // Inicializar mapa y coche
    srand(time(NULL));
    inicializar_mapa(mapa_base);
    inicializar_coches(coches);

    // Bucle principal de la simulación
    for (int turno = 0; turno < TURNOS; turno++) {
        restaurar_mapa(mapa, mapa_base);
        mover_coches(mapa, coches);
        situar_coches(mapa, coches);
        imprimir_mapa(mapa);
    }

    return 0;
}

// ---------------------------------
// Funciones de MAPA
// ---------------------------------

void inicializar_mapa(char mapa[][N]) {
    // rellenar con VACIO y CARRETERA
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == N / 2 && j == N / 2)
                mapa[i][j] = CRUCE; // cruce en el centro
            else if (i == N / 2)
                mapa[i][j] = CARRETERAH; // fila central como carretera
            else if (j == N / 2)
                mapa[i][j] = CARRETERAV; // columna central como carretera
            else
                mapa[i][j] = VACIO; // resto vacío
        }
    }
}

void restaurar_mapa(char mapa[][N], char mapa_base[][N]) {
    // copiar el mapa base al mapa actual
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mapa[i][j] = mapa_base[i][j];
}

void imprimir_mapa(char mapa[][N]) {
    // imprimir el grid por pantalla
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c", mapa[i][j]);
            // instrucción alternativa para imprimir caracters
            //putchar(mapa[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// las funciones inline se recomiendan para funciones pequeñas y muy usadas
// seria equivalente a una macro con #define pero con comprobación de tipos
inline bool dentro_mapa(int fila, int col) {
    return (fila >= 0 && fila < N && col >= 0 && col < N);
}

// ---------------------------------
// Funciones de COCHE
// ---------------------------------

void nuevo_coche(Coche *coche) {
    // coodrdenadas de las posibles entradas: arriba, derecha, abajo, izquierda
    int fila_entrada[] = { -1, N / 2, N, N / 2 };
    int col_entrada[] = { N / 2, N, N / 2, -1 };
    int dir_entrada[] = { ABAJO, IZQUIERDA, ARRIBA, DERECHA };
    // elegir una entrada aleatoria
    int entrada = rand() % 4; 
    // asignar posición y dirección inicial al coche
    coche->fila = fila_entrada[entrada];
    coche->col = col_entrada[entrada];
    coche->dir = dir_entrada[entrada];
}

void situar_coche(char mapa[][N], Coche *coche) {
    // colocar el coche en el mapa si está dentro
    if(dentro_mapa(coche->fila, coche->col)) {
        mapa[coche->fila][coche->col] = COCHE;
    }
}

void mover_coche(char mapa[][N], Coche *coche, Coche coches[]) {
    int df[] = {-1, 0, 1,  0};
    int dc[] = { 0, 1, 0, -1};
    if(coche->fila == OUT && coche->col == OUT) return;
    int nueva_fila = coche->fila + df[coche->dir];
    int nueva_col  = coche->col + dc[coche->dir];
    if (celda_ocupada(nueva_fila, nueva_col, coche->dir, coches, coche)) {
        return;
    }
    coche->fila = nueva_fila;
    coche->col = nueva_col;
    if(dentro_mapa(coche->fila, coche->col) == false) {
        coche->fila = OUT;
        coche->col = OUT;
    }
}


// ---------------------------------
// Funciones de MULTIPLES COCHES
// ---------------------------------

// Inicializa un array de coches llamando a nuevo_coche para cada uno
void inicializar_coches(Coche coches[]) {
    for (int i = 0; i < MAX_COCHES; i++) {
        nuevo_coche(&coches[i]);
    }
}

// Coloca todos los coches en el mapa si están dentro
void situar_coches(char mapa[][N], Coche coches[]) {
    for (int i = 0; i < MAX_COCHES; i++) {
        situar_coche(mapa, &coches[i]);
    }
}

// IMplemetación actual: escoge un coche para mover
// Alternativa: mueve todos los coches si la celda destino no está ocupada
void mover_coches(char mapa[][N], Coche coches[]) {
    int i = rand() % MAX_COCHES;
    mover_coche(mapa, &coches[i], coches);
}   

bool celda_ocupada(int fila, int col, int dir, Coche coches[], Coche *coche_actual) {
    // comprueba si la celda (fila, col) está ocupada por otro coche
    for (int i = 0; i < MAX_COCHES; i++) {
        if (&coches[i] == coche_actual) continue;
        if (coches[i].fila == fila && coches[i].col == col) {
            if (direcciones_opuestas(coches[i].dir, dir)) return false;
            return true;
        }
    }
    return false;
}

// Función inline para comprobar si dos direcciones son opuestas
inline bool direcciones_opuestas(int dir1, int dir2) {
    return ((dir1 + 2) % 4) == dir2;
}