/*
 * Ejercicio 1 (1 punto): Media geométrica de tres números
 * 
 * Escribe un programa en C que pida al usuario tres números enteros e imprima 
 * la media geométrica. La media geométrica de n valores se calcula como:
 * n√(x1 · x2 · ... · xn)
 */

#include <stdio.h>
#include <math.h>

int main() {
    int num1, num2, num3;
    double producto, media_geometrica;
    
    // Pedir los tres números al usuario
    printf("Introduce el primer número: ");
    scanf("%d", &num1);
    printf("Introduce el segundo número: ");
    scanf("%d", &num2);
    printf("Introduce el tercer número: ");
    scanf("%d", &num3);
    
    // Calcular el producto de los tres números
    producto = (double)num1 * num2 * num3;
    
    // Calcular la media geométrica (raíz cúbica del producto)
    media_geometrica = pow(producto, 1.0/3.0);
    
    // Imprimir el resultado
    printf("La media geométrica de %d, %d y %d es: %.2f\n", 
           num1, num2, num3, media_geometrica);
    
    return 0;
}
