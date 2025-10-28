/*
 * Ejercicio 5: Múltiplos de un número en rango
 * 
 * Solicita al usuario un número `N` (1–10). Valida la entrada. Luego muestra 
 * todos los múltiplos de `N` menores o iguales a 100.
 */

#include <stdio.h>

int main() {
    int num;
    // Pedir número hasta que sea válido
    do {
        printf("Introduce un número (1-10): ");
        scanf("%d", &num);
    } while(num < 1 || num > 10);
    // Mostrar múltiplos de N
    printf("Múltiplos de %d menores o iguales a 100:\n", num);
    for(int multiplo = num; multiplo <= 100; multiplo += num) {
        printf("%d ", multiplo);
    }
    printf("\n");
    return 0;
}
