/*
Enunciado: Define una estructura struct time que almacene dos ente-
ros representando la hora y los minutos.
Implementa una función main que cree una variable del tipo struct
time, le pida los datos al usuario y la rellene sin emplear variables adi-
cionales: escribe directamente en la estructura.
*/

#include <stdio.h>

struct time {
    int hora;
    int minutos;
};

int main() {
   // define una variable t de tipo "struct time"
    struct time t; 

    // almacena los datos dentro de la estructura
    printf("Introduce la hora (0-23): ");
    scanf("%d", &t.hora);
    printf("Introduce los minutos (0-59): ");
    scanf("%d", &t.minutos);

    printf("Hora: %02d:%02d\n", t.hora, t.minutos);
    return 0;
}
