/*
Escribe un programa en C que:
1. pida un par de horas como una cadena de cinco caracteres en for-
mato HH:MM,
2. extraiga las horas y los minutos de cada una usando la función del
enunciado 4.3
3. las valide usando la función del enunciado 4.2
4. indique la diferencia en minutos entre ellas usando la función del
enunciado 4.1
Las horas pueden haberse dado en cualquier orden, pero la diferencia
siempre debe mostrarse como un número positivo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minutos(int hora, int min) {
    return hora * 60 + min;
}

int es_valida(int hora, int min) {
    return (hora >= 0 && hora <= 23 && min >= 0 && min <= 59);
}

void obtener_hora (char *cadena, int *hora, int *min) {
    sscanf(cadena, "%d:%d", hora, min);
}


// mejora: función que obtiene y valida una hora en un paso
void obtener_hora_valida(int *hora, int *min) {
    char cadena[6];
    do {
        printf("Introduce la hora (HH:MM) > ");
        scanf("%s", cadena);
        obtener_hora(cadena, hora, min);
    } while (!es_valida(*hora, *min));
}


int main() {
    char hora1[6], hora2[6];
    int h1, m1, h2, m2;
    int min1, min2, diff;

    // Pedir y procesar la primera hora
    do {
        printf("Introduce la primera hora (HH:MM) > ");
        scanf("%s", hora1);
        obtener_hora(hora1, &h1, &m1);
    } while (!es_valida(h1, m1));

    // Pedir y procesar la segunda hora
    do {
        printf("Introduce la segunda hora (HH:MM) > ");
        scanf("%s", hora2);
        obtener_hora(hora2, &h2, &m2);
    } while (!es_valida(h2, m2));

    // El código anterior está repetido -> incluirlo en una función
    // Alternativa usando la función mejorada:
    //obtener_hora_valida(&h1, &m1);
    //obtener_hora_valida(&h2, &m2);

    // Calcular los minutos desde las 00:00
    min1 = minutos(h1, m1);
    min2 = minutos(h2, m2);

    // Calcular la diferencia absoluta
    diff = abs(min1 - min2);

    // Mostrar el resultado
    printf("Diferencia en minutos: %d\n", diff);

    return 0;
}

