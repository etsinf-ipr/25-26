/* 
programa que lanza dos dados y muestra la suma
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int lanza_dado (int caras){
    return rand() % caras + 1;
}


void lanza2dados (int *d1, int *d2){
    *d1 = rand() % 6 + 1;
    *d2 = rand() % 6 + 1;
}

int main (){
    int dado1, dado2;

    srand (time(NULL));

    dado1 = lanza_dado(6);
    dado2 = lanza_dado(20);
    printf("suma: %d\n", dado1 + dado2);

    int d3, d4;
    lanza2dados (&d3, &d4);
    printf("suma: %d\n", d3 + d4);
    return 0;
}