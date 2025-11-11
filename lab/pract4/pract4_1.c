/*
Escribe una función minutos() que reciba dos enteros: hora
y minutos, y devuelva un entero los minutos que han pasado desde las
00:00. Asume que la hora es correcta (no hay que validarla).
Escribe un programa principal para comprobar su funcionamiento, que
pida una hora al usuario y muestre los minutos que le corresponden.
*/
#include <stdio.h>

int minutos(int hora, int min) {
    return hora * 60 + min;
}

int main() {
    int h, m;
    printf("Introduce la hora (HH:MM) > ");
    scanf("%d:%d", &h, &m);
    printf("Minutos desde las 00:00: %d\n", minutos(h, m));
    return 0;
}   