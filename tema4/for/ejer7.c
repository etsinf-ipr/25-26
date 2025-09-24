/*
Leer n y contar cuántos múltiplos de 3 hay entre 1 y n.
*/

#include <stdio.h>

int main() {
    int n;
    printf("Escribe un número: ");
    scanf("%d", &n);
    int contador = 0; // inicializamos el contador a 0
    // recorremos los números desde 3 hasta n de 3 en 3
    // (solo pasamos por los múltiplos de 3)
    // si n < 3, no entra en el bucle -> contador == 0
    for (int i = 3; i <= n; i += 3) {
        // incrementamos los múltiplos de 3
        contador++;
    }
    printf("Hay %d múltiplos de 3 entre 1 y %d\n", contador, n);
    return 0;
}