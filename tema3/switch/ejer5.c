/*
 * Ejercicio 5: Define dos macros que obtengan el máximo y el mínimo entre dos 
 * valores. Usa un operador ternario. Escribe un pequeño programa para demostrar 
 * su funcionamiento.
 */

#include <stdio.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))


int main() {
    int x, y;
    printf("Introduce dos números: ");
    scanf("%d %d", &x, &y);
    printf("Máximo: %d\n", MAX(x, y));
    printf("Mínimo: %d\n", MIN(x, y));
    return 0;
}
