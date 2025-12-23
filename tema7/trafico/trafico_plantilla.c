#include <stdio.h>

#define N 10
#define VACIO '.'
#define CARRETERA '-'
#define COCHE 'C'

// Estructura básica para un coche
typedef struct _coche{
    int fila;
    int col;
    int dir; // 0=arriba, 1=derecha, 2=abajo, 3=izquierda
} Coche;

// Prototipos de funciones
void inicializar_mapa(char mapa[][N]);
void imprimir_mapa(char mapa[][N]);
void mover_coche(char mapa[][N], Coche *coche);

int main() {
    char mapa[N][N];
    Coche coche;

    // Inicializar mapa y coche
    inicializar_mapa(mapa);
    // TODO: inicializar la posición y dirección del coche

    // Bucle principal de la simulación
    for (int turno = 0; turno < 50; turno++) {
        // TODO: limpiar o actualizar mapa si es necesario

        // TODO: mover el coche
        mover_coche(mapa, &coche);
        // TODO: colocar el coche en el mapa

        // Mostrar el mapa
        imprimir_mapa(mapa);

        // TODO: cualquier otro paso del turno
    }

    return 0;
}

// TODO: implementar inicialización del mapa
void inicializar_mapa(char mapa[][N]) {
    // rellenar con VACIO y CARRETERA
}

// TODO: implementar impresión del mapa
void imprimir_mapa(char mapa[][N]) {
    // imprimir el grid por pantalla
}

// TODO: implementar movimiento del coche
void mover_coche(char mapa[][N], Coche *coche) {
    // actualizar fila/col según la dirección y reglas
}
