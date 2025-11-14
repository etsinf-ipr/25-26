/*
 * Ejercicio 1: Introducción a los vectores: carga y visualización
 * 
 * Declara un vector de 5 enteros. Pide al usuario que introduzca los valores y 
 * luego muéstralos uno por línea.
 */

#include <stdio.h>

int main() {
    int v[5];
    
    // Bucle 1: Entrada de datos
    printf("Introduce 5 números enteros:\n");
    for (int i = 0; i < 5; i++) {
        printf("Número %d: ", i + 1);
        scanf("%d", &v[i]);
    }
    
    // Bucle 2: Mostrar los valores
    printf("\nLos valores introducidos son:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d\n", v[i]);
    }
    
    return 0;
}
