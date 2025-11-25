#include <stdio.h>
#include <stdlib.h>

double pow(double x, double y){
    double res = 1;
    for(int i = 0; i < y; i++)
        res *= x;
    return res;
}

int main(int argc, char *argv[]) {

    double base = 1000;//atof(argv[1]);
    double exp = 3;//atof(argv[2]);
    double pot = pow(base, exp);
   
    printf("%g\n", pot);
    return 0;
}