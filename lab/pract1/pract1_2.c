/*
escribe un programa en C que pida una par de horas en
formato HH:MM y muestre por pantalla la diferencia en minutos entre ellas
*/

#include <stdio.h>

int main() {
    int h1, m1, h2, m2, min1, min2, diff;
    printf("Introduce una hora> ");
    scanf("%d:%d", &h1, &m1);
    printf("Introduce otra hora> ");
    scanf("%d:%d", &h2, &m2);
    min1 = h1 * 60 + m1;
    min2 = h2 * 60 + m2;
    diff = min2 - min1;
    printf("Diferencia: %d minutos\n", diff);
    return 0;
}