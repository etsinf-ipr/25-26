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
    int mayor, menor, pos_mayor, pos_menor;
    
    // Bucle 1: Entrada de datos
    printf("Introduce 10 números enteros:\n");
    for (int i = 0; i < 10; i++) {
        printf("Número %d: ", i + 1);
        scanf("%d", &v[i]);
    }
    
    // Bucle 2: Buscar mayor y menor (extensión opcional)
    mayor = v[0];
    menor = v[0];
    pos_mayor = 0;
    pos_menor = 0;
    
    for (int i = 1; i < 10; i++) {
        if (v[i] > mayor) {
            mayor = v[i];
            pos_mayor = i;
        }
        if (v[i] < menor) {
            menor = v[i];
            pos_menor = i;
        }
    }
    
    printf("\nEl mayor es %d en la posición %d\n", mayor, pos_mayor);
    printf("El menor es %d en la posición %d\n", menor, pos_menor);
    
    return 0;
}
