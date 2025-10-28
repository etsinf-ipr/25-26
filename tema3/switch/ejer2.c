/*
 * Ejercicio 2: Reescribe el programa que cuenta el número de caras y cruces 
 * usando switch
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int caras = 0, cruces = 0;

    // lanzar la moneda 100 veces. Puedes preguntarlo al usuario
    for (int i = 0; i < 100; i++) {
        int resultado = rand() % 2;
        switch (resultado) {
            case 0:
                caras++;
                break;
            case 1:
                cruces++;
                break;
        }
    }

    printf("Caras: %d\n", caras);
    printf("Cruces: %d\n", cruces);

    return 0;
}
