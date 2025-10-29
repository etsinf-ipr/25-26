/*
 * Ejercicio 4: Coseno por serie de Taylor
 * 
 * El valor de cos(x) puede aproximarse por la fórmula:
 * cos(x) = 1 – x²/2! + x⁴/4! - ... 
 * Consigue un error menor que el valor que se le pasa como parámetro.
 * 
 * Ejemplo: ./cos 1.5 0.001
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
    
    double anterior = -2; // -1 < cos(x) < 1, para que entre en el bucle
    double actual = 1;  // primer término: 1
    int n = 0;  // exponente
    
    // repite mientras el valor absoluto del término
    // sea mayor que el error permitido
    double termino = 1;
    printf("Término %d: %.10f, Suma: %.10f\n", n, termino, actual);

    while(fabs(actual - anterior) > error) {
        anterior = actual;    
        // calcular el siguiente término
        // siguiente exponente par (2, 4, 6, ...)
        n += 2;  
        // calcular el siguiente término
        termino = -termino * x * x / ((n-1) * n);  // cambio de signo y multiplicación
        actual += termino;
        // comentar para eliminar los valores intermedios
        printf("Término %d: %.10f, Suma: %.10f\n", n, termino, actual);
    }
    
    printf("cos(%.2f) ≈ %.10f\n", x, actual);
    return 0;
}
