/*
 * 3.3. Solapamiento de intervalos
 * 
 * Escribe un programa en C que pida un par de horas correspondiente al inicio 
 * y al final de un intervalo horario y otro par de horas correspondiente al 
 * inicio y final de otro intervalo horario. El programa debe mostrar por pantalla 
 * un mensaje indicando si los intervalos solapan o no. Todas las horas estarán 
 * en formato 24 horas (HH:MM) y deberán ser válidas; si alguna de ellas no lo 
 * fuera se imprimirá un mensaje informativo y no se realizará el proceso.
 */

#include <stdio.h>

int main() {
    int h1_inicio, m1_inicio, h1_fin, m1_fin;
    int h2_inicio, m2_inicio, h2_fin, m2_fin;
    
    // Leer el primer intervalo
    do{
        printf("Introduce el primer intervalo (HH:MM HH:MM): ");
        scanf("%d:%d %d:%d", &h1_inicio, &m1_inicio, &h1_fin, &m1_fin);
    }while(h1_inicio < 0 || h1_inicio > 23 || m1_inicio < 0 || m1_inicio > 59 ||
        h1_fin < 0 || h1_fin > 23 || m1_fin < 0 || m1_fin > 59);
    // Leer el segundo intervalo
    do{
        printf("Introduce el segundo intervalo (HH:MM HH:MM): ");
        scanf("%d:%d %d:%d", &h2_inicio, &m2_inicio, &h2_fin, &m2_fin);
    }while(h2_inicio < 0 || h2_inicio > 23 || m2_inicio < 0 || m2_inicio > 59 ||
        h2_fin < 0 || h2_fin > 23 || m2_fin < 0 || m2_fin > 59);
    
    // Convertir las horas a minutos desde las 00:00 para facilitar la comparación
    int inicio1 = h1_inicio * 60 + m1_inicio;
    int fin1 = h1_fin * 60 + m1_fin;
    int inicio2 = h2_inicio * 60 + m2_inicio;
    int fin2 = h2_fin * 60 + m2_fin;
    
    // Verificar si los intervalos solapan
    // Dos intervalos NO solapan si uno termina antes de que empiece el otro
    if (fin1 < inicio2 || fin2 < inicio1) 
        printf("Los intervalos NO solapan.\n");
    else 
        printf("Los intervalos SI solapan.\n");
    
    return 0;
}
