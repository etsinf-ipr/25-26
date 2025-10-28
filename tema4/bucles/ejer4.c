/*
 * Ejercicio 4: Contar valores válidos e inválidos
 * 
 * Pide al usuario números enteros. El programa termina cuando se introduce un cero. 
 * Debe mostrar cuántos números válidos (mayores que cero) y cuántos inválidos 
 * (menores que cero) se introdujeron.
 */

#include <stdio.h>

int main() {
    int num, validos = 0, invalidos = 0;
    printf("Introduce números enteros (0 para terminar):\n");
    //bucle mientras el número no sea cero
    do {
        // leemos un nuevo número
        printf("> ");
        scanf("%d", &num);
        // contamos según sea válido o inválido
        if(num > 0)
            validos++;
        else if(num < 0)
            invalidos++;
    } while(num != 0);
    // mostramos los resultados
    printf("Números válidos: %d\n", validos);
    printf("Números inválidos: %d\n", invalidos);
    return 0;
}
