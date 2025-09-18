/*
    Usa `scanf` para leer un número entero y luego imprímelo con `printf`.
*/

#include <stdio.h>

int main() {
    int numero;
    printf("Introduce un número entero: ");
    scanf("%d", &numero);
    printf("El número es: %d\n", numero);
    return 0;
}