#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n, i, esOblongo = 0;

    srand(time(NULL));
    n = rand() % 100;
    printf("Número generado: %d\n", n);

    for (i = 0; i < 100; i++) {
        if (i * (i + 1) == n) {
            printf("%d es un número oblongo (%d * %d)\n", n, i, i + 1);
            esOblongo = 1;
            break;
        }
    }

    if (!esOblongo)
        printf("%d no es un número oblongo\n", n);

    return 0;
}