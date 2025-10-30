#include <stdio.h>
#include <math.h>

int main() {
    int a, b, c;
    printf("Introduce tres números\n");
    scanf("%d%d%d", &a, &b, &c);
    // tambien se pueden hacer tres scanf separados
    printf("La media geométrica es: %f\n",
            pow((a * b * c), 1/3.0));
}
