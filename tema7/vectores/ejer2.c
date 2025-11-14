/*
 * Ejercicio 2: Recorrido e impresión inversa
 * 
 * Pide al usuario 10 números enteros, guárdalos en un vector y muéstralos en orden 
 * inverso al introducido.
 */

#include <stdio.h>

int main() {
    int v[10];
    
    // Bucle 1: Entrada de datos
    printf("Introduce 10 números enteros:\n");
    for (int i = 0; i < 10; i++) {
        printf("Número %d: ", i + 1);
        scanf("%d", &v[i]);
    }
    
    // Bucle 2: Mostrar en orden inverso
    printf("\nLos valores en orden inverso son:\n");
    for (int i = 9; i >= 0; i--) {
        printf("%d\n", v[i]);
    }
    
    return 0;
}
