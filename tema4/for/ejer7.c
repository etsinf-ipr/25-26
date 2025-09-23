/*
Leer n y contar cuántos múltiplos de 3 hay entre 1 y n.

Pista: el resto de la división entera se obtiene
con el operador % (módulo)
Ejemplo: 10 % 3 = 1, 9 % 3 = 0, 8 % 3 = 2

Los divisores entre 3 son aquellos números
que al dividirlos entre 3 dan resto 0.
*/

#include <stdio.h>

int main() {
    int n;
    printf("Escribe un número: ");
    scanf("%d", &n);
    int contador = 0; // inicializamos el contador a 0
    for (int i = 1; i <= n; i++) {
        if (i % 3 == 0) { // si i es múltiplo de 3
            contador++;   // incrementamos el contador
        }
    }
    printf("Hay %d múltiplos de 3 entre 1 y %d\n", contador, n);
    return 0;
}