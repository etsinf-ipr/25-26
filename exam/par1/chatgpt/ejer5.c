#include <stdio.h>
#include <math.h>

int main() {
    int a, b, raizSuma, raizResta;

    for (a = 1; a < 100; a++) {
        for (b = a + 1; b < 100; b++) {

            raizSuma = (int) sqrt(a + b);
            raizResta = (int) sqrt(b - a);

            if (raizSuma * raizSuma == a + b && raizResta * raizResta == b - a) {
                printf("(%d, %d)\n", a, b);
            }
        }
    }

    return 0;
}
