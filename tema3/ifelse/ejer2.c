/*
 * Ejercicio 2: Leer un número entero e imprimir un mensaje indicando si es positivo o negativo
 * 
 * Descripción: Programa que lee un número y determina si es positivo o negativo
 */

#include <stdio.h>

int main() {
    // Declaración de variables
    int numero;
    
    // Entrada de datos
    printf("Introduce un número entero: ");
    scanf("%d", &numero);
    
    // Procesamiento con if-else
    if (numero > 0) {
        // Salida de resultados
        printf("El número %d es positivo.\n", numero);
    } else if (numero < 0) {
        printf("El número %d es negativo.\n", numero);
    } else {
        printf("El número es cero.\n");
    }
    
    return 0;
}
