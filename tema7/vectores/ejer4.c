/*
 * Ejercicio 4: Conteo condicional
 * 
 * Pide 10 números enteros y cuenta cuántos son positivos y cuántos negativos. 
 * Muestra los totales al final.
 */

#include <stdio.h>

int main() {
    int v[10];
    int positivos, negativos;
    
    // Bucle 1: Entrada de datos
    printf("Introduce 10 números enteros:\n");
    for (int i = 0; i < 10; i++) {
        printf("Número %d: ", i + 1);
        scanf("%d", &v[i]);
    }
    
    // Bucle 2: Contar positivos y negativos
    positivos = 0;
    negativos = 0;
    for (int i = 0; i < 10; i++) {
        if (v[i] > 0) {
            positivos++;
        } else if (v[i] < 0) {
            negativos++;
        }
    }
    
    printf("\nNúmeros positivos: %d\n", positivos);
    printf("Números negativos: %d\n", negativos);
    
    return 0;
}
