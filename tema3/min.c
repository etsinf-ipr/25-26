#include <stdio.h>


int main() {
    int a, b;

    printf("numeros: ");
    scanf("%d", &a);
    scanf("%d", &b);

    int min;
    if ( a < b)
        min = a;
    else 
        min = b;

    
    min = (a<b) ? a : b;
    printf("el menor es %d\n", min);

    return 0;
}