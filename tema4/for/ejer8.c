/*
Escribe un código en C que genere la siguiente secuencia 
usando un bucle for
i=1, suma=1 
i=2, suma=3 
i=3, suma=6 
i=4, suma=10 
i=5, suma=15

Pista:
i.  suma
1.  1
2.  1+2=3
3.  3+3=6
4.  6+4=10
5.  10+5=15

*/

#include <stdio.h>

int main() {
    int suma = 0; // inicializamos la suma a 0
    for (int i = 1; i <= 5; i++) {
        suma += i; // acumulamos la suma
        printf("i=%d, suma=%d\n", i, suma);
    }
    return 0;
}