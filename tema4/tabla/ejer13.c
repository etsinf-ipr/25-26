/*
    Ajusta la salida para que coincidan unidades y decenas
*/

#include <stdio.h>

int main() {
    int numero;
    printf("Introduce un número entero: ");
    scanf("%d", &numero);

    for (int i = 1; i <= 10; i++) {
        printf("%d x %2d = %d\n", numero, i, numero * i);
    }
    return 0;
}
