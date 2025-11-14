/*
 * Ejercicio 3: Cálculo de suma y promedio
 * 
 * Lee 8 valores reales en un vector. Calcula e imprime su suma y su promedio.
 */

#include <stdio.h>

int main() {
    float v[8];
    float suma;
    
    // Bucle 1: Entrada de datos
    printf("Introduce 8 valores reales:\n");
    for (int i = 0; i < 8; i++) {
        printf("Valor %d: ", i + 1);
        scanf("%f", &v[i]);
    }
    
    // Bucle 2: Calcular suma
    suma = 0;
    for (int i = 0; i < 8; i++) {
        suma += v[i];
    }
    
    printf("\nSuma: %.2f\n", suma);
    printf("Promedio: %.2f\n", suma / 8);
    
    return 0;
}
