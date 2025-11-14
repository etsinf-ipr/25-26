/*
 * Ejercicio 6: Detección de valores repetidos
 * 
 * Lee 6 números enteros y comprueba si hay algún valor repetido.
 * Muestra un mensaje indicando si el vector contiene duplicados o no.
 */

#include <stdio.h>

int main() {
    int v[6];
    
    // Bucle 1: Entrada de datos
    printf("Introduce 6 números enteros:\n");
    for (int i = 0; i < 6; i++) {
        printf("Número %d: ", i + 1);
        scanf("%d", &v[i]);
    }
    
    // Bucle 2: Buscar duplicados
    int hay_duplicados = 0;
    for (int i = 0; i < 6 && !hay_duplicados; i++) {
        for (int j = i + 1; j < 6; j++) {
            if (v[i] == v[j]) {
                hay_duplicados = 1;
            }
        }
    }
    
    if (hay_duplicados) {
        printf("\nEl vector contiene valores duplicados.\n");
    } else {
        printf("\nEl vector NO contiene valores duplicados.\n");
    }
    
    return 0;
}
