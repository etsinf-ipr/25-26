/*
 * Ejercicio 6: Tablas de multiplicar
 * 
 * Muestra las tablas de multiplicar de todos los números del 1 al 10.
 * 
 * Sugerencia: Dentro de un bucle podemos tener cualquier código, incluido otro 
 * bucle. Revisa el ejercicio de la tabla de multiplicar sencilla y modifícalo.
 */

#include <stdio.h>

int main() {
    for(int i = 1; i <= 10; i++) {
        printf("\nTabla del %d:\n", i);
        for(int j = 1; j <= 10; j++) {
            printf("%2d x %2d = %2d\n", i, j, i * j);
        }
        printf("\n");
    }   
    
    return 0;
}
