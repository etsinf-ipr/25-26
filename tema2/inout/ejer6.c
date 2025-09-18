/*
    Imprime el número tanto en formato decimal como en formato hexadecimal con `%h
*/

#include <stdio.h>

int main() {
    int numero = 255;
    printf("Número en decimal: %d\n", numero);
    printf("Número en hexadecimal: %x\n", numero);
    // con # incluye una marca que indica la base de numeración
    printf("Número en decimal: %d\n", 10);
    printf("Número en hexadecimal: %#x\n", 16);
    return 0;
}