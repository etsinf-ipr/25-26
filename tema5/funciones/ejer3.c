/*
 * Ejercicio 3: Función que devuelve un valor
 * 
 * Crea una función doble(n) que devuelva el doble del número recibido.
 * Escribe un programa que la use desde main().
 */

#include <stdio.h>

int doble(int n) {
    return n * 2;
}

int main() {
    int numero, resultado;
    
    printf("Introduce un número: ");
    scanf("%d", &numero);
    
    resultado = doble(numero);
    
    printf("El doble de %d es %d\n", numero, resultado);
    
    return 0;
}
