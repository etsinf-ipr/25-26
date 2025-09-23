/*
Escribe un bucle for que genera la siguiente secuencia 
1 3 5 7 9 11 13 15 17 19
*/

#include <stdio.h>

int main() {
    for (int i = 1; i < 20; i += 2) {
        printf("%d ", i);
    }
    // Salto de línea al final
    printf("\n");
    return 0;
}
