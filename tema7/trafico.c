#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define N 10    
#define TURNOS 20
#define OUT    -N   
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
bool dentro_mapa(Coche *coche);


int main() {
    char mapa[N][N];       // mapa actual con coches
    char mapa_base[N][N];  // mapa base para restaurar cada turno
    Coche coche;

    // Inicializar mapa y coche
    srand(time(NULL));
    inicializar_mapa(mapa_base);
    // TODO: inicializar la posición y dirección del coche
    nuevo_coche(&coche);

    // Bucle principal de la simulación
    for (int turno = 0; turno < TURNOS; turno++) {
        // TODO: limpiar o actualizar mapa si es necesario
        restaurar_mapa(mapa, mapa_base);
        // TODO: mover el coche
        mover_coche(mapa, &coche);
        // TODO: colocar el coche en el mapa
        situar_coche(mapa, &coche);
        // Mostrar el mapa
        imprimir_mapa(mapa);

        // TODO: cualquier otro paso del turno
    }

    return 0;
}

// TODO: implementar inicialización del mapa
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
    if(dentro_mapa(coche)) {
        mapa[coche->fila][coche->col] = COCHE;
    }
}

// TODO: implementar impresión del mapa
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

// TODO: implementar movimiento del coche
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
    if(dentro_mapa(coche) == false) {
        coche->fila = OUT;
        coche->col = OUT; 
    }
}

// las funciones inline son recomendables para funciones pequeñas y muy usadas
inline bool dentro_mapa(Coche *coche) {
    return (coche->fila >= 0 && coche->fila < N && coche->col >= 0 && coche->col < N);
}