/* 
Indica qué hace el siguiente código 
mostrando los valores de las variables en cada paso 
¿Cuál es el resultado?
*/

#include <stdio.h>

int main() {
    int resultado = 1; 
    int n = 5;
    for (int i = 1; i <= n; i++) 
        resultado *= i; 
    printf("resultado =  %d\n", resultado);
    return 0;
}

/*
RESPUESTA:

n.   i.    resultado
5.   1.    1
5.   2.    2
5.   3.    6
5.   4.    24
5.   5.    120

resultado = 1x2x3x4x5 = 120 = 5!

El código calcula el factorial de n (5! = 120)
*/