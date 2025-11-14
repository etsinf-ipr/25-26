/*
 * Ejercicio 2: Función con un parámetro simple
 * 
 * Define una función cuadrado(n) que muestre el cuadrado del número recibido.
 * El main() debe pedir un número al usuario y llamar a la función.
 */

#include <stdio.h>

void cuadrado(int n) {
    printf("El cuadrado de %d es %d\n", n, n * n);
}

int main() {
    int numero;
    
    printf("Introduce un número: ");
    scanf("%d", &numero);
    
    cuadrado(numero);
    
    return 0;
}
