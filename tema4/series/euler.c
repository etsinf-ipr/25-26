/*
 * Ejercicio 5: Aproximación de pi según la fórmula de Euler
 * 
 * Aproxima el valor de pi según la fórmula de Euler. 
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

    // bucle para el número de términos indicado
    for (int i = 1; i <= n_terminos; i++) {
        pi += 1.0 / (i * i);
        // comentar para no mostrar los valores intermedios
        printf("pi : %.5f\n", pi);
        
    }
    pi = sqrt(pi * 6.0);
    printf("pi = %.10f\n",  pi);
    return 0;
}
