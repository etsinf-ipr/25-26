/*
 * Ejercicio 1: Escribe un programa en C que indique si un número que introduce 
 * el usuario es múltiplo de 3 y de 5 (a la vez), de uno de los dos o de ninguno 
 * de los dos.
 */

#include <stdio.h>

int main() {
    int numero;
    printf("Introduce un número entero: ");
    scanf("%d", &numero);

    if (numero % 3 == 0 && numero % 5 == 0) {
        printf("El número es múltiplo de 3 y 5.\n");
    } else if (numero % 3 == 0) {
        printf("El número es múltiplo de 3.\n");
    } else if (numero % 5 == 0) {
        printf("El número es múltiplo de 5.\n");
    } else {
        printf("El número no es múltiplo de 3 ni de 5.\n");
    }

    return 0;
}