/*
 * Ejercicio 3: Leer un número entero e indicar si es par o impar
 * Nota: el operador % calcula el resto de la división entera. Se usa como +, -, * y /
 * 
 * Descripción: Programa que determina la paridad de un número usando el operador módulo
 */

#include <stdio.h>

int main() {
    // Declaración de variables
    int numero;
    
    // Entrada de datos
    printf("Introduce un número entero: ");
    scanf("%d", &numero);
    
    // Procesamiento con if-else
    if (numero % 2 == 0) {
        // Salida de resultados
        printf("El número %d es par.\n", numero);
    } else {
        printf("El número %d es impar.\n", numero);
    }
    
    return 0;
}
