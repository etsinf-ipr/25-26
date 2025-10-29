/*
 * Ejercicio 8: Aproximación de pi según la fórmula de Wallis
 * 
 * Aproxima el valor de pi según la fórmula de Wallis:
 * π/2 = (2/1) * (2/3) * (4/3) * (4/5) * (6/5) * (6/7) * ...
 * π/2 = ∏(n=1 to ∞) [(2n)²]/[(2n-1)(2n+1)]
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
    double pi = 1.0;  // empezamos con 1 para el producto

    // bucle para el número de términos indicado
    for (int n = 1; n <= n_terminos; n++) {
        double numerador = (2.0 * n) * (2.0 * n);      // (2n)²
        double denominador = (2.0 * n - 1) * (2.0 * n + 1);  // (2n-1)(2n+1)
        pi *= numerador / denominador;
        // comentar para no mostrar los valores intermedios
        printf("pi : %.5f\n", pi * 2);
    }
    
    pi = pi * 2.0;  // π = 2 * (π/2)
    printf("pi = %.10f\n", pi);
    return 0;
}
