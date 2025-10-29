/*
 * Ejercicio 7: Aproximación de pi según la fórmula de Sharp
 * 
 * Aproxima el valor de pi según la fórmula de Sharp:
 * π = 6 * arctan(1/√3) = 6 * (1/√3 - (1/√3)³/3 + (1/√3)⁵/5 - ...)
 * Usa la línea de comandos para indicar el número de términos.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <n_terminos>\n", argv[0]);
        return 1;
    }
    int n_terminos = atoi(argv[1]);
    double pi = 0.0;
    double x = 1.0 / sqrt(3.0);  // 1/√3
    double termino = x;
    int signo = 1;

    // bucle para el número de términos indicado
    for (int i = 0; i < n_terminos; i++) {
        pi += signo * termino / (2 * i + 1);
        termino *= x * x;  // siguiente potencia de (1/√3)
        signo = -signo;    // alternar signo
        // comentar para no mostrar los valores intermedios
        printf("pi : %.5f\n", pi * 6);
    }
    
    pi = pi * 6.0;  // π = 6 * arctan(1/√3)
    printf("pi = %.10f\n", pi);
    return 0;
}
