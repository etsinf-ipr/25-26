// pares cuadrados menos de 100

#include <stdio.h>
#include <math.h>

int main() {
    for (int p = 0; p <= 100; p++) {
        for (int n = p + 1; n <= 100; n++) {
            float root1 = sqrt(n + p);
            float root2 = sqrt(n - p);
            if ((root1 == floor(root1)) && (root2 == floor(root2))) {
                printf("%d %d\n", p, n);
            }
        }
    }
    return 0;
}