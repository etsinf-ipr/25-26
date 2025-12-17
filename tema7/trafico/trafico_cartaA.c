/*
Ampliación Carta A – Calles aleatorias
Generar aleatoriamente 2 calles horizontales y 2 verticales completas.
Deben estar separadas por una distancia mínima (al menos una diferencia de 2)
Los coches pueden salir de cualquiera de los extremos de las carreteras
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

// Devuelve el tipo de celda: VACIO, CARRETERAH, CARRETERAV o CRUCE
typedef struct {
    int filas_h[2];
    int cols_v[2];
} Calles;

// Prototipos de funciones
void inicializar_mapa(char mapa[][N], Calles *calles);
void imprimir_mapa(char mapa[][N]);
void mover_coche(char mapa[][N], Coche *coche);
// funciones añadidas
void restaurar_mapa(char mapa[][N], char mapa_base[][N]);
void nuevo_coche(Coche *coche, Calles *calles);
void situar_coche(char mapa[][N], Coche *coche);
bool dentro_mapa(int fila, int col);
// funciones para la ampliación: calles aleatorias
void generar_calles(Calles *calles);
char tipo_carretera(int i, int j, Calles *calles);


int main() {
    char mapa[N][N];       // mapa actual con coches
    char mapa_base[N][N];  // mapa base para restaurar cada turno
    Coche coche;
    Calles calles;

    // Inicializar mapa y coche
    srand(time(NULL));
    generar_calles(&calles);
    inicializar_mapa(mapa_base, &calles);
    nuevo_coche(&coche, &calles);

    // Bucle principal de la simulación
    for (int turno = 0; turno < TURNOS; turno++) {
        restaurar_mapa(mapa, mapa_base);
        mover_coche(mapa, &coche);
        situar_coche(mapa, &coche);
        imprimir_mapa(mapa);
    }

    return 0;
}

// ---------------------------------
// Funciones de CALLES ALEATORIAS
// ---------------------------------

void generar_calles(Calles *calles) {
    // Primera fila y columna en la primera mitad (sin bordes)
    calles->filas_h[0] = 1 + rand() % ((N/2) - 1);
    calles->cols_v[0] = 1 + rand() % ((N/2) - 1);

    // Segunda fila y columna en la segunda mitad (sin bordes)
    calles->filas_h[1] = (N/2) + 1 + rand() % (N - (N/2) - 2);
    calles->cols_v[1] = (N/2) + 1 + rand() % (N - (N/2) - 2);
}

char tipo_carretera(int i, int j, Calles *calles) {
    // Determina si la celda (i,j) es VACIO, CARRETERAH, CARRETERAV o CRUCE
    int es_h = (i == calles->filas_h[0] || i == calles->filas_h[1]);
    int es_v = (j == calles->cols_v[0] || j == calles->cols_v[1]);
    if (es_h && es_v) return CRUCE;
    if (es_h) return CARRETERAH;
    if (es_v) return CARRETERAV;
    return VACIO;
}

// ---------------------------------
// Funciones de MAPA
// ---------------------------------

void inicializar_mapa(char mapa[][N], Calles *calles) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            mapa[i][j] = tipo_carretera(i, j, calles);
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

inline bool dentro_mapa(int fila, int col) {
    return (fila >= 0 && fila < N && col >= 0 && col < N);
}


// ---------------------------------
// Funciones de COCHE
// ---------------------------------

void nuevo_coche(Coche *coche, Calles *calles) {
    int extremos = 8;
    int filas[8], cols[8], dirs[8];
    int k = 0;

    // Extremos horizontales (izquierda y derecha)
    for (int i = 0; i < 2; i++) {
        filas[k] = calles->filas_h[i]; cols[k] = 0;    dirs[k++] = DERECHA;
        filas[k] = calles->filas_h[i]; cols[k] = N-1;  dirs[k++] = IZQUIERDA;
    }
    // Extremos verticales (arriba y abajo)
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
	// colocar el coche en el mapa si está dentro
    if(dentro_mapa(coche->fila, coche->col)) {
		mapa[coche->fila][coche->col] = COCHE;
	}
}


void mover_coche(char mapa[][N], Coche *coche) {
	// actualizar fila/col según la dirección y reglas
	int df[] = {-1, 0, 1,  0}; // cambios en fila    para ARRIBA, DERECHA, ABAJO, IZQUIERDA
	int dc[] = { 0, 1, 0, -1}; // cambios en columna para ARRIBA, DERECHA, ABAJO, IZQUIERDA
	// el coche está fuera del mapa
	if(coche->fila == OUT && coche->col == OUT) return;
	// mover el coche (se puede hacer con un switch en lugar de vectores)
	coche->fila += df[coche->dir];
	coche->col += dc[coche->dir];
	// comprobar si ha salido del mapa
	if(dentro_mapa(coche->fila, coche->col) == false) {
		coche->fila = OUT;
		coche->col = OUT; 
	}
}





