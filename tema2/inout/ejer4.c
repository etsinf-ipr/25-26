/*
    Usando `scanf`, lee una cadena y luego imprímela.
*/

#include <stdio.h>

int main() {
    char nombre[100];
    printf("Introduce tu nombre: ");
    scanf("%s", nombre);
    printf("Hola, %s\n", nombre);
    return 0;
}