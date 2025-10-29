/*
 * Ejercicio 4: Coseno por serie de Taylor
 * 
 * El valor de cos(x) puede aproximarse por la fórmula:
 * cos(x) = 1 – x²/2! + x⁴/4! - ... 
 * Escribe un programa en C que reciba por línea de comandos
 * un número y el número de términos, y calcule el coseno
 * 
 * Ejemplo: ./cos 1.5 10
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
    double resultado = 1.0;  // primer término: 1
    double termino = 1.0;

    // bucle para el número de términos indicado
    for (int i = 1; i < n_terminos; i++) {
        // calcular el siguiente término: -x²/2!, +x⁴/4!, etc.
        termino = -termino * x * x / ((2*i-1) * (2*i));
        resultado += termino;
        // comentar para eliminar los valores intermedios
        printf("x: %.5f\n", resultado);
    }

    printf("Coseno de %.2f: %.5f\n", x, resultado);
    return 0;
}
