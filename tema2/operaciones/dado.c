/* simula el lanzamiento de una dado */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    srand(time(NULL));

    for( int i = 0; i < 100; i++){
        int dado = rand() % 6 + 1;

        printf("%d ", dado);
    }
    printf("\n");

    return 0;
}
