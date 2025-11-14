/*
 * Ejercicio 6: Traza de función con llamada múltiple
 * 
 * Observa la función:
 * int f(int x) {
 *     return x * 2 + 1;
 * }
 * 
 * a) Traza manualmente qué valores devuelve f(0), f(1), f(2) y f(f(2)).
 * b) Implementa el código para usarla y verifica los resultados.
 */

#include <stdio.h>

int f(int x) {
    return x * 2 + 1;
}

int main() {
    printf("Traza de la función f(x) = x * 2 + 1:\n\n");
    
    printf("f(0) = %d\n", f(0));
    printf("f(1) = %d\n", f(1));
    printf("f(2) = %d\n", f(2));
    printf("f(f(2)) = f(%d) = %d\n", f(2), f(f(2)));
    
    return 0;
}
