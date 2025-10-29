/*
 * Ejercicio 3: Seno por serie de Taylor
 * 
 * El valor de sen(x) puede aproximarse por la fórmula:
 * sen(x) = x – x³/3! + x⁵/5! - ... 
 * Consigue un error menor que el valor que se le pasa como parámetro.
 * 
 * Ejemplo: ./sen 1.5 0.001
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <x> <error>\n", argv[0]);
        return 1;
    }
    // obtiene los parámetros de la línea de comandos
    double x = atof(argv[1]);
    double error = atof(argv[2]);
    
    double anterior = -2; // -1 < sen(x) < 1, para 
    double actual = x;  // primer término: x
    int n = 1;  // exponente
    
    // repite mientras el valor absoluto del término
    // sea mayor que el error permitido
    double termino = x;
    printf("Término %d: %.10f, Suma: %.10f\n", n, termino, actual);

    while(fabs(actual - anterior) > error) {
        anterior = actual;    
        // calcular el siguiente término
        // siguiente exponente impar (3, 5, 7, ...)
        n += 2;  
        // calcular el siguiente término
        termino = -termino * x * x / ((n-1) * n);  // cambio de signo y multiplicación
        actual += termino;
        // comentar para eliminar los valores intermedios
        printf("Término %d: %.10f, Suma: %.10f\n", n, termino, actual);
    }
    
    printf("sen(%.2f) ≈ %.10f\n", x, actual);
    return 0;
}
