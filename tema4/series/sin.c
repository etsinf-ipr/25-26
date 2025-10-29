/*
 * Ejercicio 3: Seno por serie de Taylor
 * 
 * El valor de sen(x) puede aproximarse por la fórmula:
 * sen(x) = x – x³/3! + x⁵/5! - ... 
 * Escribe un programa en C que reciba por línea de comandos
 * un número y el número de términos, y calcule el seno
 * 
 * Ejemplo: ./sin 1.5 10
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <numero> <n_terminos>\n", argv[0]);
        return 1;
    }
    // obtiene los parámetros de la línea de comandos
    double x = atof(argv[1]);
    int n_terminos = atoi(argv[2]);
    double resultado = x;  // primer término: x
    double termino = x;

    // bucle para el número de términos indicado
    for (int i = 1; i < n_terminos; i++) {
        // calcular el siguiente término: -x³/3!, +x⁵/5!, etc.
        termino = -termino * x * x / ((2*i) * (2*i+1));
        resultado += termino;
        // comentar para eliminar los valores intermedios
        printf("x: %.5f\n", resultado);
    }

    printf("Seno de %.2f: %.5f\n", x, resultado);
    return 0;
}
