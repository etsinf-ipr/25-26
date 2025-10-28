/*
 * Ejercicio 4: Obtén el valor absoluto de un número que introduce el usuario. 
 * Utiliza un operador ternario.
 */

#include <stdio.h>

int main() {
    int num;
    
    printf("Introduce un número: ");
    scanf("%d", &num);
    int abs_val = (num < 0) ? -num : num;
    printf("|%d| = %d\n", num, abs_val);
    
    return 0;
}
