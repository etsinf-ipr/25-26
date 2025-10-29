/*
 * Ejercicio 1: Raíz cuadrada por el método de Newton
 * 
 * La raíz cuadrada de un número puede aproximarse por el método de Newton que 
 * sigue esta fórmula: xn+1 = 1/2 (xn + (2 / xn)). 
 * Consigue un error menor que el valor que se le pasa como parámetro.
 * 
 * Ejemplo: ./raiz 12 0.001
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <numero> <error>\n", argv[0]);
        return 1;
    }
    // obtiene los parámetros de la línea de comandos
    double numero = atof(argv[1]);
    double error = atof(argv[2]);
    double x = 1;
    double x_ant = 0;

    // repite mientras la diferencia entre dos iteraciones
    // sea mayor que el error permitido
    while(fabs(x - x_ant) > error ) {
        x_ant = x;
        x = 0.5 * (x_ant + (numero / x_ant));
        // comentar para eliminar los valores intermedios
        printf("x: %.5f\n", x);
    }

    printf("Raíz cuadrada de %.2f: %.5f\n", numero, x);
    return 0;
}
