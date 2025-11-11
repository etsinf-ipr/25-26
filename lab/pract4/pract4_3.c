/*
Escribe un programa en C con una función que, dada una
cadena de cinco caracteres que representan una hora válida en formato
HH:MM, y dos enteros pasados por referencia, devuelva en esos enteros
las horas y minutos correspondientes
Escribe una función main para probar que funciona correctamente
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void obtener_hora (char *cadena, int *hora, int *min) {
    char shora[6];
    char *token;
    // para no modificar la cadena original
    strcpy(shora, cadena);
    token = strtok(shora, ":");
    *hora = atoi(token);
    token = strtok(NULL, ":");
    *min = atoi(token);
    // alternativa con sscanf:
    //sscanf(cadena, "%d:%d", hora, min);
    // OJO: hora y min no llevan & porque ya son punteros
}

int main() {
    char cadena[6];
    int h, m;
    printf("Introduce la hora (HH:MM) > ");
    scanf("%s", cadena);
    obtener_hora(cadena, &h, &m);
    printf("Hora: %02d, Minutos: %02d\n", h, m);
    return 0;
}   