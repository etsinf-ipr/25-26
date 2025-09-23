/*
Calcular la suma de los enteros de 1 hasta n   
*/

#include <stdio.h>  

int main() {
    int n;
    printf("Escribe un número: ");
    scanf("%d", &n);
    // aquí vamos a dejar la suma
    // es obligatorio inicializar a 0
    int suma = 0;
    for (int i = 1; i <= n; i++) {
        suma += i; // equivalente a suma = suma + i
    }
    printf("La suma es %d\n", suma);
    return 0;
}