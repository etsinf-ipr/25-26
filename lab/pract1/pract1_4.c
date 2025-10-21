/*
escribe un programa en C que pida un par de horas (forma-
to 24 horas) con formato HH:MM. Si ambas horas son válidas, se mostrarán
en orden cronológico; en otro caso, se mostrará un mensaje indicando
que la entrada no ha sido correcta
*/

#include <stdio.h>
// variante con macros
// #define es_correcta(h,m) (h >= 0 && h <= 23 && m >= 0 && m <= 59

    int main() {
    int h1, m1, h2, m2, min1, min2, diff;
    printf("Introduce una hora> ");
    scanf("%d:%d", &h1, &m1);
    printf("Introduce otra hora> ");
    scanf("%d:%d", &h2, &m2);
    // if (es_correcta(h1,m1) && es_correcta(h2,m2))
    if (h1 >= 0 && h1 <= 23 && m1 >= 0 && m1 <= 59 &&
        h2 >= 0 && h2 <= 23 && m2 >= 0 && m2 <= 59) {
        int min1 = h1 * 60 + m1;
        int min2 = h2 * 60 + m2;
        if(min1 < min2)
            printf("%02d:%02d - %02d:%02d\n", h1, m1, h2, m2);
        else
            printf("%02d:%02d - %02d:%02d\n", h2, m2, h1, m1);
    }
    else {
        printf("Las horas no son correctas\n");
    }
    return 0;
}