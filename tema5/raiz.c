#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[]) {

    double n = atof(argv[1]);
    double r = sqrt(n);
    printf("%g\n", r);
    return 0;
}