/*
Enunciado: escribe un programa en C que pida dos horas, represen-
tadas en formato 24 horas, con formato HH:MM. El programa imprimirá
por pantalla la secuencia minuto a minuto desde la primera hora a la
segunda hora, ambas incluidas. Asume que las horas con correctas y se
introducen en orden creciente (la menor primero)
Por ejemplo, si las horas son 18:55 y 19:03, imprimirá 18:55, 18:56,
18:57, 18:58, 18:59, 19:00, 19:01, 19:02.
*/

#include <stdio.h>

int main() {
    int h1, m1, h2, m2;

    // Leer las dos horas
    printf("Introduce la primera hora (HH:MM): ");
    scanf("%d:%d", &h1, &m1);
    printf("Introduce la segunda hora (HH:MM): ");
    scanf("%d:%d", &h2, &m2);

    int min1 = h1 * 60 + m1; // Convertir la primera hora a minutos
    int min2 = h2 * 60 + m2; // Convertir la segunda hora a minutos

    // Imprimir la secuencia de minutos
    for (int m = min1; m <= min2; m++) {
        // Convertir minutos de vuelta a formato HH:MM 
        // La división entera da las horas y el resto los minutos
        // Ej: 150 min = 2h 30m -> 150/60 = 2, 150%60 = 30
        printf("%02d:%02d\n", m / 60, m % 60);
    }

    return 0;
}
    }

    return 0;
}