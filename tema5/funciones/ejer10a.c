/*
 * Ejercicio 10: Cálculo combinado con funciones auxiliares
 * 
 * Diseña un programa que calcule la media y el rango de tres números reales usando 
 * dos funciones:
 * - media(a, b, c)
 * - rango(a, b, c) que devuelva la diferencia entre el mayor y el menor.
 * 
 * El main() debe pedir los tres números, llamar a ambas funciones y mostrar los 
 * resultados.
 */

#include <stdio.h>

float media(float a, float b, float c) {
    return (a + b + c) / 3.0;
}

float rango(float a, float b, float c) {
    float mayor = a;
    float menor = a;
    
    if (b > mayor) mayor = b;
    if (c > mayor) mayor = c;
    
    if (b < menor) menor = b;
    if (c < menor) menor = c;
    
    return mayor - menor;
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
