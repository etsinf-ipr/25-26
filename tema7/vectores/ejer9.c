/*
 * Ejercicio 9: Función para búsqueda en vector
 * 
 * Implementa una función buscar(v, n, x) que devuelva la posición del elemento x 
 * dentro del vector v o -1 si no se encuentra (n es el tamaño del vector).
 * El main() debe pedir los datos, llamar a la función y mostrar el resultado.
 */

#include <stdio.h>

int buscar(int v[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (v[i] == x) {
            return i;
        }
    }
    return -1;
}

int main() {
    int v[10];
    int n = 10;
    int x, posicion;
    
    // Bucle 1: Entrada de datos
    printf("Introduce 10 números enteros:\n");
    for (int i = 0; i < n; i++) {
        printf("Número %d: ", i + 1);
        scanf("%d", &v[i]);
    }
    
    printf("\nIntroduce el número a buscar: ");
    scanf("%d", &x);
    
    // Buscar usando la función
    posicion = buscar(v, n, x);
    
    if (posicion != -1) {
        printf("El número %d se encuentra en la posición %d\n", x, posicion);
    } else {
        printf("El número %d no se encuentra en el vector\n", x);
    }
    
    return 0;
}
