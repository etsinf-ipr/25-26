/*
 * Ejercicio 9: Paso de parámetros por referencia
 * 
 * Crea una función intercambiar(a, b) que intercambie los valores de dos enteros 
 * usando variables auxiliares.
 * Comprueba en main() que las variables cambian después de llamar a la función.
 */

#include <stdio.h>

void intercambiar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x, y;
    
    printf("Introduce el primer número: ");
    scanf("%d", &x);
    printf("Introduce el segundo número: ");
    scanf("%d", &y);
    
    printf("\nAntes del intercambio: x = %d, y = %d\n", x, y);
    
    intercambiar(&x, &y);
    
    printf("Después del intercambio: x = %d, y = %d\n", x, y);
    
    return 0;
}
