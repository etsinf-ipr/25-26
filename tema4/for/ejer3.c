/*
Leer un número N y mostrar 
los pares desde 2 hasta N (incluído)
*/

#include <stdio.h>

int main() {
    int n;
    printf("Escribe un número: ");
    scanf("%d", &n);
    // si n es par, se para en n
    // si es impar, se para en n-1s
    for (int i = 2; i <= n; i += 2) {
        printf("%d\n", i);
    }
    return 0;
}
