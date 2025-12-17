/*
Ampliación Carta E – Generación periódica de coches
Cada X turnos, aparece un coche nuevo en la entrada
Pueden aparecer a un ritmo fijo o variable (aleatorio)
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

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

// Prototipos de funciones
void inicializar_mapa(char mapa[][N]);
void imprimir_mapa(char mapa[][N]);
void mover_coche(char mapa[][N], Coche *coche);
// funciones añadidas
void restaurar_mapa(char mapa[][N], char mapa_base[][N]); 
void nuevo_coche(Coche *coche);
void situar_coche(char mapa[][N], Coche *coche);
bool dentro_mapa(int fila, int col);
// funciones para la ampliaciónPrototipos de funciones para la generación de coches (Carta E)
typedef enum { FIJA, UNIF, EXP } llegada_t;
int entrada_fija(int turno, int periodo);
int entrada_uniforme(int turno, double probabilidad);
int entrada_exponencial(int turno, double lambda);
int entrada(int turno, llegada_t tipo, double param);


int main() {
    char mapa[N][N];       // mapa actual con coches
    char mapa_base[N][N];  // mapa base para restaurar cada turno
    Coche coche;

    // Inicializar mapa y coche
    srand(time(NULL));
    inicializar_mapa(mapa_base);
    nuevo_coche(&coche);
    
    // Bucle principal de la simulación
    for (int turno = 0; turno < TURNOS; turno++) {
        // ejemplo: cada 10 turnos
        // OJO: si es menos de 10 turnos el otro coche desaparecerá
        if (entrada(turno, EXP, 0.5)) { 
            nuevo_coche(&coche);
        }
        restaurar_mapa(mapa, mapa_base);
        mover_coche(mapa, &coche);
        situar_coche(mapa, &coche);
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

// ---------------------------------
// Funciones de ENTRADA COCHES
// ---------------------------------


int entrada_fija(int turno, int periodo) {
    //genera un coche cada 'periodo' turnos.
    return (turno % periodo == 0);
}


int entrada_uniforme(int turno, double probabilidad) {
    // genera un coche con probabilidad 'probabilidad' cada turno
    // por ejemplo, probabilidad=0.2 genera un coche en el 20% de los turnos
    // valores altos generan coches muy seguidos (max 1)
    return ((double)rand() / RAND_MAX) < probabilidad;
}


int entrada_exponencial(int turno, double lambda) {
    // genera un coche según un proceso de Poisson con tasa 'lambda'
    // está basado el la teoría de colas y tiempos entre llegadas
    // valores altos generan coches muy seguidos
    double p = 1 - exp(-lambda);
    return ((double)rand() / RAND_MAX) < p;
}


int entrada(int turno, llegada_t tipo, double param) {      
    // función para decidir si en el turno actual entra un coche
    switch (tipo) {
        case FIJA:
            return entrada_fija(turno, (int)param);
        case UNIF:
            return entrada_uniforme(turno, param);
        case EXP:
            return entrada_exponencial(turno, param);
        default:
            return 0;
    }
}

