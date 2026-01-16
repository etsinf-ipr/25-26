/*
Ampliación Carta B – Semáforos coordinados
Añadir semáforos en los cruces.
Estados globales:
	Verde horizontal / rojo vertical
	Rojo horizontal / verde vertical
Cambian cada cierto número de turnos.
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
#define CICLO_SEMAFORO 4 // número de turnos por ciclo del semáforo

// Estructura básica para un coche
enum DIRECTION { ARRIBA, DERECHA, ABAJO, IZQUIERDA };
typedef struct _coche{
	int fila;
	int col;
	int dir; // 0=arriba, 1=derecha, 2=abajo, 3=izquierda
} Coche;

// Estructura y funciones para semáforo coordinado
typedef enum { VERDE_H, VERDE_V } EstadoSemaforo;
typedef struct {
    int fila;
    int col;
    EstadoSemaforo estado;
} Semaforo;

// Prototipos de funciones
void inicializar_mapa(char mapa[][N]);
void imprimir_mapa(char mapa[][N], const Semaforo *semaforo);
void mover_coche(char mapa[][N], Coche *coche, const Semaforo *semaforo);
// funciones añadidas
void restaurar_mapa(char mapa[][N], char mapa_base[][N]); 
void nuevo_coche(Coche *coche);
void situar_coche(char mapa[][N], Coche *coche);
bool dentro_mapa(int fila, int col);
// funciones para la amplicación: semáforo coordinado 
void inicializar_semaforo(Semaforo *semaforo);
void actualizar_semaforo(Semaforo *semaforo, int turno);
bool puede_pasar(int direccion, const Semaforo *semaforo);
bool en_cruce(Coche *coche);
bool es_cruce(int fila, int col);
char simbolo_cruce(const Semaforo *semaforo);


int main() {
	char mapa[N][N];       // mapa actual con coches
	char mapa_base[N][N];  // mapa base para restaurar cada turno
	Coche coche;
	Semaforo semaforo;

	// Inicializar mapa y coche
	srand(time(NULL));
	inicializar_mapa(mapa_base);
	inicializar_semaforo(&semaforo);
	nuevo_coche(&coche);

	// Bucle principal de la simulación
	for (int turno = 0; turno < TURNOS; turno++) {
		restaurar_mapa(mapa, mapa_base);
        // Ciclo de 5 turnos para el semáforo
		actualizar_semaforo(&semaforo, turno); 
		mover_coche(mapa, &coche, &semaforo);
		situar_coche(mapa, &coche);
		imprimir_mapa(mapa, &semaforo);
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

void situar_coche(char mapa[][N], Coche *coche) {
    // colocar el coche en el mapa si está dentro
    if(dentro_mapa(coche->fila, coche->col)) {
        mapa[coche->fila][coche->col] = COCHE;
    }
}

void imprimir_mapa(char mapa[][N], const Semaforo *semaforo) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (es_cruce(i, j)) {
                putchar(mapa[i][j] == COCHE ? COCHE : simbolo_cruce(semaforo));
            } else {
                putchar(mapa[i][j]);
            }
        }
        putchar('\n');
    }
    putchar('\n');
}

inline bool dentro_mapa(int fila, int col) {
    return (fila >= 0 && fila < N && col >= 0 && col < N);
}

inline bool es_cruce(int fila, int col) {
    return fila == N/2 && col == N/2;
}

inline char simbolo_cruce(const Semaforo *semaforo) {
    return semaforo->estado == VERDE_H ? CARRETERAH : CARRETERAV;
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
	int entrada = 3;//rand() % 4; 
	// asignar posición y dirección inicial al coche
	coche->fila = fila_entrada[entrada];
	coche->col = col_entrada[entrada];
	coche->dir = dir_entrada[entrada];
}


void mover_coche(char mapa[][N], Coche *coche, const Semaforo *semaforo) {
    // actualizar fila/col según la dirección y reglas
    int df[] = {-1, 0, 1,  0};
    int dc[] = { 0, 1, 0, -1};
    if(coche->fila == OUT && coche->col == OUT) return;
    int nueva_fila = coche->fila + df[coche->dir];
    int nueva_col  = coche->col + dc[coche->dir];
    // Comprobar si puede avanzar según el semáforo
    if (!dentro_mapa(nueva_fila, nueva_col)) {
        coche->fila = OUT;
        coche->col = OUT;
        return;
    }
    // Si el siguiente paso es el cruce, comprobar semáforo antes de entrar
    if (es_cruce(nueva_fila, nueva_col) && !puede_pasar(coche->dir, semaforo)) {
        return;
    }
    coche->fila = nueva_fila;
    coche->col  = nueva_col;
}

inline bool en_cruce(Coche *coche) {
    return es_cruce(coche->fila, coche->col);
}


// ---------------------------------
// Funciones de SEMÁFORO
// ---------------------------------

void inicializar_semaforo(Semaforo *semaforo) {
    // Colocar el semáforo en el cruce central
    semaforo->fila = N/2;
    semaforo->col = N/2;
    semaforo->estado = VERDE_H;
}


void actualizar_semaforo(Semaforo *semaforo, int turno) {
    // Cambiar el estado del semáforo cada CICLO_SEMAFORO turnos
    semaforo->estado = (turno / CICLO_SEMAFORO) % 2 == 0 ? VERDE_H : VERDE_V;
}

bool puede_pasar(int direccion, const Semaforo *semaforo) {
    if (semaforo->estado == VERDE_H && (direccion == DERECHA || direccion == IZQUIERDA))
        return true;
    if (semaforo->estado == VERDE_V && (direccion == ARRIBA || direccion == ABAJO))
        return true;
    return false;
}
