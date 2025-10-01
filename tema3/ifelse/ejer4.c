/*
 * Ejercicio 4: Leer un número y validar que esté en el rango [1, 100]
 * 
 * Descripción: Programa que verifica si un número está dentro del rango permitido
 */

#include <stdio.h>

int main() {
    // Declaración de variables
    int numero;
    
    // Entrada de datos
    printf("Introduce un número: ");
    scanf("%d", &numero);
    
    // Procesamiento con if-else
    if (numero >= 1 && numero <= 100) {
        // Salida de resultados
        printf("El número %d está en el rango válido [1, 100].\n", numero);
    } else {
        printf("El número %d NO está en el rango válido [1, 100].\n", numero);
    }
    
    return 0;
}
