/*
escribe un programa en C que pida un par de enteros
correspondientes a horas y minutos y los muestre por pantalla con el
formato HH:MM (dos dígitos para hora y dos para minutos).
*/

#include <stdio.h>

int main() {

    int hora, min;

    printf("Introduce una hora (hh:mm)> ");
    scanf("%d:%d", &hora, &min);
    printf("%02d:%02d\n", hora, min);

    return 0;
}