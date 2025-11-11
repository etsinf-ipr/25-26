/*
Escribe un programa en C con una función que valide una
hora en formato HH:MM y con el formato correcto). La función recibirá dos
enteros: la hora y los minutos, y devolverá 1 si forman una hora válida
y 0 en caso contrario.
Implementar la función main que pida horas en el ese formato y repita
el proceso hasta que la hora sea válida, momento en que se imprimirá
por pantalla.
*/

#include <stdio.h>

int es_valida(int hora, int min) {
    if (hora >= 0 && hora <= 23 && min >= 0 && min <= 59)
        return 1;
    else
        return 0;
    //version condensada (habitual):
    //return (hora >= 0 && hora <= 23 && min >= 0 && min <= 59);
}

int main() {
    int h, m;
    do {
        printf("Introduce la hora (HH:MM) > ");
        scanf("%d:%d", &h, &m);
    } while (!es_valida(h, m));
    printf("Hora válida: %02d:%02d\n", h, m);
    return 0;
}