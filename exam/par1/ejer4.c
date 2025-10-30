#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    srand(time(NULL));
    int num = rand() % 100;
    
    for(int factor = 0; factor*factor <= num; factor++){
        if(factor * (factor + 1) == num){
            printf("%d = %d x %d\n", num, factor, factor + 1);
            return 0;
        }
    }
    printf("%d no es un número oblongo\n", num);
    return 0;
}s