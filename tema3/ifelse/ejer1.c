/*
 * Ejercicio 1: Leer un número entero e imprimir un mensaje solo si es positivo
 * 
 * Descripción: Programa que lee un número y muestra un mensaje únicamente si es positivo
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
    }
    
    return 0;
}
