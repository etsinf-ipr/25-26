/*
 * Ejercicio 4: Función con varios parámetros
 * 
 * Define una función promedio(a, b, c) que calcule y devuelva el promedio de tres 
 * números reales.
 * El programa debe mostrar el resultado formateado con dos decimales.
 */

#include <stdio.h>

float promedio(float a, float b, float c) {
    return (a + b + c) / 3.0;
}

int main() {
    float num1, num2, num3, resultado;
    
    printf("Introduce tres números reales:\n");
    printf("Número 1: ");
    scanf("%f", &num1);
    printf("Número 2: ");
    scanf("%f", &num2);
    printf("Número 3: ");
    scanf("%f", &num3);
    
    resultado = promedio(num1, num2, num3);
    
    printf("El promedio es: %.2f\n", resultado);
    
    return 0;
}
