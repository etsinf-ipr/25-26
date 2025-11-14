/*
 * Ejercicio 10: Inserción controlada en vector ordenado (difícil)
 * 
 * Dado un vector de 10 enteros ordenados de menor a mayor, pide un nuevo número e 
 * insértalo en su posición correcta, desplazando los elementos si es necesario.
 * (No se requiere mantener más de 10 elementos; puedes perder el último.)
 */

#include <stdio.h>

int main() {
    int v[10];
    int nuevo, posicion;
    
    // Bucle 1: Entrada de datos (vector ordenado)
    printf("Introduce 10 números enteros en orden creciente:\n");
    for (int i = 0; i < 10; i++) {
        printf("Número %d: ", i + 1);
        scanf("%d", &v[i]);
    }
    
    printf("\nIntroduce el nuevo número a insertar: ");
    scanf("%d", &nuevo);
    
    // Bucle 2: Encontrar posición e insertar
    posicion = 0;
    for (int i = 0; i < 10; i++) {
        if (nuevo > v[i]) {
            posicion = i + 1;
        } else {
            break;
        }
    }
    
    // Desplazar elementos hacia la derecha
    for (int i = 9; i > posicion; i--) {
        v[i] = v[i - 1];
    }
    
    // Insertar el nuevo elemento
    v[posicion] = nuevo;
    
    // Mostrar el vector resultante
    printf("\nVector después de la inserción:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
    
    return 0;
}
