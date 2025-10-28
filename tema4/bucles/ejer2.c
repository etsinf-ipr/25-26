/*
 * Ejercicio 2: Suma de números positivos
 * 
 * El usuario introduce números enteros positivos. El programa termina cuando se 
 * introduce un número negativo y muestra la suma total de los positivos ingresados.
 */

#include <stdio.h>

int main() {
    int num = 0, suma = 0;
    printf("Introduce números enteros positivos (número negativo para terminar):\n");
    //bucle mientras los números sean positivos
    while (num >= 0) {
        // leemos un nuevo número
        printf("> ");
        scanf("%d", &num);
        // si el número es negativo, lo ignoramos
        if(num > 0)
            suma += num;
    }
    // mostramos la suma total
    printf("Total: %d\n", suma);
    return 0;
}
