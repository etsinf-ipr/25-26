/*
 * Ejercicio 2: Logaritmo natural por serie de Taylor
 * 
 * El logaritmo de x+1 puede aproximarse con la fórmula:
 * ln(x+1) = x – x²/2 + x³/3 - ... 
 * Consigue un error menor que el valor que se le pasa como parámetro.
 * 
 * Ejemplo: ./log 3 0.001
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
    double x = atof(argv[1])-1;
    double error = atof(argv[2]);
    
    double x_ant = 0; // log(0) no está definido -> entra en el bucle
    int n = 1;  // denominador
    
    // repite mientras la diferencia entre dos iteraciones
    // sea mayor que el error permitido
    double termino = x, x_new = x;
    while(fabs(x_ant - x_new) > error) {
        x_ant = x_new;
        // calcular el siguiente término
        n++;  // siguiente denominador (2, 3, 4, ...)
        // calcular el siguiente término: -x²/2, +x³/3, -x⁴/4, ...
        termino = -termino * x;  // cambio de signo y potencia
        x_new  += termino / n;
        // comentar para eliminar los valores intermedios
        printf("x: %.5f\n", x_new);
    }

    printf("ln(%.2f) = %.5f\n", x+1, x_new);
    return 0;
}
