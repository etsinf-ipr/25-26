/*
 * Ejercicio 6: Haz una traza del siguiente código y explica qué hace
 */

#include <stdio.h>

int main() {
    int a, n, res = 0;

    scanf("%d", &a);
    for (int i = 1; i <= a; i++) {
        scanf("%d", &n);
        if (n > 0)
            res++;
    }
    printf("%d\n", res);
    return 0;
}

/*
 * TRAZA DEL PROGRAMA (Entrada: 5 -2 7 6 3 -1):
 * 
 * | Paso | a | i | n  | res | Condición (n > 0) |
 * |------|---|---|----|-----|-------------------|
 * | 1    | 5 | ? | ?  | 0   | -                 |
 * | 2    | 5 | 1 | -2 | 0   | -2 > 0 = FALSO   |
 * | 3    | 5 | 2 | 7  | 1   | 7 > 0 = VERDAD   |
 * | 4    | 5 | 3 | 6  | 2   | 6 > 0 = VERDAD   |
 * | 5    | 5 | 4 | 3  | 3   | 3 > 0 = VERDAD   |
 * | 6    | 5 | 5 | -1 | 3   | -1 > 0 = FALSO   |
 * | 7    | 5 | 6 | -1 | 3   | -                 |
 * 
 * EXPLICACIÓN:
 * Este programa cuenta cuántos números positivos hay en una secuencia.
 * Lee 'a' números y por cada número positivo incrementa 'res'.
 * Resultado: 3 números positivos (7, 6 y 3) de 5 números leídos.
 */