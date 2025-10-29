/*
 * Ejercicio 6: Aproximación de pi según la fórmula de Leibniz
 * 
 * Aproxima el valor de pi según la fórmula de Leibniz:
 * π/4 = 1 - 1/3 + 1/5 - 1/7 + 1/9 - ...
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
    int signo = 1;

    // bucle para el número de términos indicado
    for (int i = 0; i < n_terminos; i++) {
        double termino = signo * 1.0 / (2 * i + 1);
        pi += termino;
        signo = -signo;  // alternar signo
        // comentar para no mostrar los valores intermedios
        printf("pi : %.5f\n", pi * 4);
    }
    
    pi = pi * 4.0;  // π = 4 * (π/4)
    printf("pi = %.10f\n", pi);
    return 0;
}
