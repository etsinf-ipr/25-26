#include <stdio.h>
#include <math.h>

int main() {
    int a, b, c;
    double media;

    printf("Introduce tres números enteros: ");
    scanf("%d %d %d", &a, &b, &c);

    media = pow((a * b * c), 1.0 / 3.0);

    printf("La media geométrica es: %.2f\n", media);
    return 0;
}