/*
 * 3.1. Validar una hora
 * 
 * Escribe un programa en C que pida una hora en formato HH:MM 
 * El proceso de petición de datos debe repetirse hasta que la hora
 * sea válida (entre 00:00 y 23:59 y con el formato correcto), y en ese
 * momento se imprimirá por pantalla.
 */

#include <stdio.h>

int main() {
    int horas, minutos;
    
    // se repite mientras la hora no sea válida
    do{
        printf("Introduce una hora (HH:MM): ");
        scanf("%d:%d", &horas, &minutos);
    }while(horas < 0 || horas > 23 || minutos < 0 || minutos > 59); 

    printf("Hora válida: %02d:%02d\n", horas, minutos);
    return 0;
}
