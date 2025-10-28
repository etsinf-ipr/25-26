/*
 * Ejercicio 3: Números primos
 * 
 * Solicita al usuario un número `N`. Indica si el número es primo.
 */

#include <stdio.h>

int main() {
    int num, es_primo = 1;
    printf("Introduce un número entero positivo: ");
    scanf("%d", &num);
    // recorremos los números desde 3 hasta la mitad de num
    // 0, 1 y 2 son primos
    // si num=7 (por ejemplo), no hace falta llegar a 6
    // cualquier número > 4 no es divisor de 7 
    // 7 / 4 = 1,x, así que el único divisor posible que queda es 1
    for(int i = 3; i <= num / 2; i++) {
        if(num % i == 0) {
            es_primo = 0;
            // si encomtramos un divisor, salimos del bucle 
            break;
        }
    }
    if(num < 2) {
    
    return 0;
}
