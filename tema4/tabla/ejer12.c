/*
    Pregunta al usuario un número entero y escribe su tabla de multiplicar 
*/

#include <stdio.h>

int main() {
    int numero;
    printf("Introduce un número entero: ");
    scanf("%d", &numero);

    for (int i = 1; i <= 10; i++) {
        printf("%d x %d = %d\n", numero, i, numero * i);
    }
    return 0;
}
