/*
 * Ejercicio 5: Búsqueda del máximo (mínimo)
 * 
 * Carga 10 enteros en un vector y determina cuál es el mayor (menor). Muestra su 
 * posición dentro del vector.
 * 
 * Extensión opcional: modifica el programa para que obtenga el mayor y el menor 
 * en el mismo bucle.
 */

#include <stdio.h>

int main() {
    int v[10];
    int mayor, pos_mayor;
    
    // Bucle 1: Entrada de datos
    printf("Introduce 10 números enteros:\n");
    for (int i = 0; i < 10; i++) {
        printf("Número %d: ", i + 1);
        scanf("%d", &v[i]);
    }
    
    // Bucle 2: Buscar el mayor
    mayor = v[0];
    pos_mayor = 0;
    
    for (int i = 1; i < 10; i++) {
        if (v[i] > mayor) {
            mayor = v[i];
            pos_mayor = i;
        }
    }
    
    printf("\nEl mayor es %d en la posición %d\n", mayor, pos_mayor);
    
    return 0;
}
