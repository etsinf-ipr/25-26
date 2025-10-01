/*
 * Ejercicio 5: Leer 10 números y mostrar si cada uno es par o impar
 * 
 * Descripción: Programa que procesa una secuencia de 10 números y determina su paridad
 */

#include <stdio.h>

int main() {
    // Declaración de variables
    int numero;
    
    // Entrada de datos y procesamiento
    printf("Introduce 10 números enteros:\n");
    
    for (int i = 1; i <= 10; i++) {
        printf("Número %d: ", i);
        scanf("%d", &numero);
        
        // Procesamiento con if-else
        if (numero % 2 == 0) {
            // Salida de resultados
            printf("El número %d es par.\n", numero);
        } else {
            printf("El número %d es impar.\n", numero);
        }
    }
    
    return 0;
}
