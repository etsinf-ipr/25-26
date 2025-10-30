#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n, suma = 0;

    if (argc != 2) {
        printf("Uso: %s número\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);

    while (n > 0) {
        suma += n % 10;
        n /= 10;
    }

    printf("suma: %d\n", suma);
    return 0;
}