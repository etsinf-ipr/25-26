/*
 * Ejercicio 10b: Cálculo combinado con funciones auxiliares (versión con inline)
 * 
 * Diseña un programa que calcule la media y el rango de tres números reales usando 
 * dos funciones:
 * - media(a, b, c)
 * - rango(a, b, c) que devuelva la diferencia entre el mayor y el menor.
 * 
 * Esta versión define funciones inline para menor y mayor que se usan dentro de rango.
 * 
 * El main() debe pedir los tres números, llamar a ambas funciones y mostrar los 
 * resultados.
 */

#include <stdio.h>

// Alternativa a #define, usando funciones inline (más seguras)
// Funciones inline para calcular menor y mayor de dos números
static inline float menor(float x, float y) {
    return (x < y) ? x : y;
}

static inline float mayor(float x, float y) {
    return (x > y) ? x : y;
}

float media(float a, float b, float c) {
    return (a + b + c) / 3.0;
}

float rango(float a, float b, float c) {
    // Usar las funciones inline para encontrar el menor y mayor
    float min = menor(menor(a, b), c);
    float max = mayor(mayor(a, b), c);
    
    return max - min;
}

int main() {
    float num1, num2, num3;
    
    printf("Introduce tres números reales:\n");
    printf("Número 1: ");
    scanf("%f", &num1);
    printf("Número 2: ");
    scanf("%f", &num2);
    printf("Número 3: ");
    scanf("%f", &num3);
    
    printf("\nMedia: %.2f\n", media(num1, num2, num3));
    printf("Rango: %.2f\n", rango(num1, num2, num3));
    
    return 0;
}
