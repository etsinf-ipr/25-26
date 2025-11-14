/*
 * Ejercicio 8: Función para calcular promedio
 * 
 * Crea una función promedio(v, n) que reciba un vector de enteros v y su tamaño, 
 * y devuelva el promedio.
 * El programa principal debe leer los valores y mostrar el resultado usando esa función.
 */

#include <stdio.h>

float promedio(int v[], int n) {
    float suma = 0;
    for (int i = 0; i < n; i++) {
        suma += v[i];
    }
    // como suma es float no hace la división entera
    return suma / n;
}

int main() {
    int v[10];
    int n = 10;
    
    // Bucle 1: Entrada de datos
    printf("Introduce 10 números enteros:\n");
    for (int i = 0; i < n; i++) {
        printf("Número %d: ", i + 1);
        scanf("%d", &v[i]);
    }
    
    // Calcular y mostrar el promedio usando la función
    printf("\nEl promedio es: %.2f\n", promedio(v, n));
    
    return 0;
}
