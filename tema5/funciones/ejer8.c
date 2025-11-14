/*
 * Ejercicio 8: Traza de función con bucle interno
 * 
 * La función int suma_hasta(int n) devuelve la suma de los números de 1 a n.
 * 
 * a) Traza los valores intermedios que toma i y suma para n = 4.
 * b) Implementa el código y verifica los resultados.
 */

#include <stdio.h>

int suma_hasta(int n) {
    int suma = 0;
    for (int i = 1; i <= n; i++) {
        suma += i;
        printf("i = %d, suma = %d\n", i, suma);
    }
    return suma;
}

int main() {
    int n = 4;
    int resultado;
    
    printf("Traza de suma_hasta(%d):\n", n);
    resultado = suma_hasta(n);
    printf("\nResultado final: %d\n", resultado);
    
    return 0;
}
