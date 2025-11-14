/*
 * Ejercicio 5: Función que devuelve un valor lógico (condicional simple)
 * 
 * Escribe una función es_par(n) que devuelva 1 si el número es par y 0 si es impar.
 * Desde main(), pide un número, llama a la función y muestra el resultado como 
 * "El número es par" o "El número es impar".
 */

#include <stdio.h>

int es_par(int n) {
    return (n % 2 == 0);
}

int main() {
    int numero;
    
    printf("Introduce un número: ");
    scanf("%d", &numero);
    
    if (es_par(numero)) {
        printf("El número es par\n");
    } else {
        printf("El número es impar\n");
    }
    
    return 0;
}
