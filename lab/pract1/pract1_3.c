/*
escribe un programa en C que pida una hora en formato
HH:MM; la hora se imprimirá sólo si es válida (entre 00:00 y 23:59 y con el
formato correcto
*/

#include <stdio.h>

int main() {

    int hora, min;

    printf("Introduce una hora (hh:mm)> ");
    scanf("%d:%d", &hora, &min);
    if (hora >= 0 && hora <= 23 && min >= 0 && min <= 59) {
        printf("%02d:%02d\n", hora, min);
    }

    return 0;
}