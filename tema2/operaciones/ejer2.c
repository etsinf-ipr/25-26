/*
  Ejercicio 2: Escribe un programa en C que multiplica dos números enteros a x b 
  usando la técnica de la multiplicación rusa. 
  Sugerencia: resuelve primero el caso de que b sea una potencia de dos y 
  luego modifícalo para resolver el caso general.
 */

#include <stdio.h>

int main() {
    // Declaración de variables
    int a, b;
    int resultado = 0;
    
    printf("Introduce el primer número (a): ");
    scanf("%d", &a);
    printf("Introduce el segundo número (b): ");
    scanf("%d", &b);
    printf( "%d x %d = ", a, b);
    
    while (b > 1) {
        if (b % 2 == 1) {
            resultado += a;
            b--;
        }
        a *= 2; // a = a * 2;
        b /= 2; // b = b / 2;
    }
    
    printf("%d\n", resultado + a);
    
    return 0;
}