/*
 * Ejercicio 7: Números primos
 * 
 * Muestra los números primos menores de 100.
 */

#include <stdio.h>

int main() {
    // bucle que recorre todos los números desde 2 hasta 99
    for(int num = 2; num < 100; num++) {
        int es_primo = 1;
        // bucle para comprobar si num es primo (ver ejer 3)
        for(int i = 2; i <= num / 2; i++) {
            if(num % i == 0) {
                es_primo = 0;
                break;
            }
        }
        if(es_primo) {
            printf("%d ", num);
        }
    }
    
    return 0;
}
