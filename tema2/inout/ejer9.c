/*
    Pregunta el nombre y la edad de la persona e imprímela
*/

#include <stdio.h>

int main() {
    char nombre[100];
    int edad;
    printf("Introduce tu nombre: ");
    scanf("%s", nombre);
    printf("Introduce tu edad: ");
    scanf("%d", &edad);
    printf("Hola, %s. Tienes %d años.\n", nombre, edad);
    return 0;
}