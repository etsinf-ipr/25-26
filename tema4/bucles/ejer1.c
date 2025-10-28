/*
 * Ejercicio 1: Validación de entrada
 * 
 * Solicita al usuario una nota entre 0 y 10. Si la nota no es válida, vuelve a 
 * pedirla hasta que lo sea. Luego muestra la nota ingresada.
 */

#include <stdio.h>

int main() {
    float nota;
    do {
        printf("Introduce una nota (0-10): ");
        scanf("%f", &nota);
    } while (nota < 0 || nota > 10);
    printf("Nota válida: %.2f\n", nota);
    return 0;
}
