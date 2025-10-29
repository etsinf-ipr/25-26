/*
 * Ejercicio 2: Logaritmo natural por serie de Taylor
 * 
 * El logaritmo de x+1 puede aproximarse con la fórmula:
 * ln(x+1) = x – x²/2 + x³/3 - ... 
 * Escribe un programa en C que reciba por línea de comandos
 * un número y el número de términos, y calcule el logaritmo natural
 * 
 * Ejemplo: ./log 3 10
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
    double numero = atof(argv[1]);
    int n_terminos = atoi(argv[2]);
    double x = numero - 1;  // ln(x+1), así que usamos x-1
    double resultado = 0.0;
    double termino = x;  // primer término: x

    // bucle para el número de términos indicado
    for (int i = 1; i <= n_terminos; i++) {
        resultado += termino / i;
        // comentar para eliminar los valores intermedios
        printf("x: %.5f\n", resultado);
        
        // calcular el siguiente término: cambio de signo y potencia
        termino = -termino * x;
    }

    printf("Logaritmo natural de %.2f: %.5f\n", numero, resultado);
    return 0;
}
