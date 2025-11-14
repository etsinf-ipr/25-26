/*
 * Ejercicio 7: Búsqueda secuencial de un valor
 * 
 * Declara un vector de 10 enteros y pide un número a buscar.
 * Recorre el vector y muestra si el número se encuentra (o "no encontrado" si no está).
 * 
 * Variación opcional: Lo mismo, pero devolviendo 1) la posición, 2) las dos cosas 
 * (número y posición).
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
    
    int buscar;
    printf("\nIntroduce el número a buscar: ");
    scanf("%d", &buscar);
    
    // Bucle 2: Búsqueda secuencial
    // usando la posición como "flag" no hace falta la variable "encontrado"
    int posicion = -1;
    for (int i = 0; i < 10; i++) {
        if (v[i] == buscar) {
            posicion = i;
            break;
        }
    }
    
    if (posicion >= 0) {
        printf("El número %d se encuentra en la posición %d\n", buscar, posicion);
    } else {
        printf("No encontrado\n");
    }
    
    return 0;
}
