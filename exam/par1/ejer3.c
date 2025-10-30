/* suma los dígitos de un número */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int num;
    int suma = 0;
    int cifra;

    num = atoi(argv[1]);

    while(num > 0){
        cifra = num % 10;
        suma += cifra;
        num /= 10;
    }
    printf("suma: %d\n", suma);
    return 0;
}