#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TIME 20

int inactivo(int M[][16]) {
    // recorre las columnas (sensores)
    for( int s = 0; s < 16; s++ ) {
        int activos = 0;     // hay que inicializarlo para cada sensor
        // recorre todas las filas (activaciones de un sensor)
        for (int t = 0; t < MAX_TIME; t++){
            if (M[t][s] > 0){ // también == 1 o != 0
                activos++;
                // si encuentra una activación no hace falta seguir
                break; 
            }
        }
        // el sensor s no se ha activado -> termina
        if (activos == 0) return s;
    }
    // si llega aquí, todos los sensores se han activado
    return -1;
}

// versión 2 con while
int inactivow(int M[][16]) {
    // recorre las columnas (sensores)
    for( int s = 0; s < 16; s++ ) {
        int activos = 0, t = 0;
        while (M[t][s] == 0 && t < MAX_TIME)
            t++;
        // no ha encontrado ninguna activación -> termina
        if (t == MAX_TIME) return s;
    }
    // si llega aquí, todos los sensores se han activado
    return -1;
}


// inicializa la matriz de activaciones (no es parte del examen)
void inicializar_matriz(int M[][16]) {
    srand(time(NULL));
    for (int t = 0; t < MAX_TIME; t++) {
        for (int s = 0; s < 16; s++) {
            // 70% de probabilidad de inactivo (0)
            M[t][s] = (rand() % 10 < 1) ? 1 : 0;
        }
    }
}   

// imprime la matriz de activaciones (no es parte del examen)
void print(int M[][16]) {
    printf("Matriz de activaciones:\n");
    for (int t = 0; t < MAX_TIME; t++) {
        for (int s = 0; s < 16; s++) {
            printf("%d ", M[t][s]);
        }
        printf("\n");
    }
}

int main() {
    // matriz de activaciones de sensores (0=inactivo, 1=activo)
    int M[MAX_TIME][16];

    // inicializa la matriz (no es parte del examen)
    inicializar_matriz(M);
    print(M);
    // llama a la función
    int s = inactivo(M);
    printf("sensor inactivo (for): %d\n", s);
    s = inactivow(M);
    printf("sensor inactivo (while): %d\n", s);
}