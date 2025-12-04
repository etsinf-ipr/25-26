/*
Comparador de barajado: 40 intercambios aleatorios vs Fisher-Yates (39 intercambios).
Ambos métodos hacen aproximadamente el mismo número de intercambios.

MÉTRICAS EXPLICADAS:

1. CHI-CUADRADO (χ²):
   - Mide si la distribución de posiciones es UNIFORME (todas igual de probables)
   - Ejemplo: barajamos 100,000 veces y contamos dónde acaba la carta 0
   - Si fuera uniforme: cada posición debería tener ~2500 apariciones (100000/40)
   - Chi² = Σ[(observado - esperado)² / esperado] para cada posición
   - Valor ideal: cerca de 39 (grados de libertad = N-1 = 40-1)
   - Si Chi² >> 39: el barajado está SESGADO (algunas posiciones más probables)
   
2. DESVIACIÓN SOBRE ESPERADO:
   - Es la mayor diferencia entre lo observado y lo esperado
   - Esperado por posición: 100000/40 = 2500 apariciones
   - Si una posición tiene 12352 apariciones: desviación = 12352-2500 = 9852
   - En un barajado perfecto: la desviación máxima es pequeña (~100)
   - Desviación grande = sesgo claro hacia ciertas posiciones
   
3. PUNTOS FIJOS:
   - Carta que queda en su posición ORIGINAL después de barajar
   - Ejemplo: si la carta en posición 5 sigue en posición 5 → punto fijo
   - En una permutación aleatoria uniforme: promedio = 1.0 punto fijo
   - Si puntos fijos >> 1: muchas cartas no se han movido (mal barajado)
   - Es una propiedad matemática: E[puntos_fijos] = N/N = 1 para cualquier N
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 40
#define TRIALS 100000

static inline void swap_int(int *a, int *b){ int t=*a; *a=*b; *b=t; }

static void crear(int v[]){
    for(int i=0;i<N;i++) v[i]=i;
}

static void barajar_swaps(int v[]){
    for(int k=0;k<40;k++){
        int i = rand()%N;
        int j = rand()%N;
        swap_int(&v[i], &v[j]);
    }
}

static void barajar_yates(int v[]){
    for(int i=N-1;i>0;i--){
        int j = rand()%(i+1);
        swap_int(&v[i], &v[j]);
    }
}

static void evalua(const char *nombre, void (*barajar)(int v[])){
    int deck[N];
    long counts[N]={0};
    long long total_fixed=0;

    clock_t t0 = clock();
    for(int t=0;t<TRIALS;t++){
        crear(deck);
        barajar(deck);
        // Uniformidad: contar en qué posición acaba la carta 0
        // (podría ser cualquier carta, la 0 es arbitraria)
        for(int i=0;i<N;i++){ if(deck[i]==0){ counts[i]++; break; } }
        // Puntos fijos: cartas que NO se movieron de su posición original
        int fixed=0; for(int i=0;i<N;i++){ if(deck[i]==i) fixed++; }
        total_fixed += fixed;
    }
    clock_t t1 = clock();

    double secs = (double)(t1-t0)/CLOCKS_PER_SEC;
    double us_per_shuffle = secs*1e6/TRIALS;

    // Calcular Chi-cuadrado para medir uniformidad
    double expected = (double)TRIALS/N; // apariciones esperadas por posición
    double chi2=0.0; long max_dev=0; int max_pos=-1;
    for(int i=0;i<N;i++){
        double diff = counts[i]-expected;
        chi2 += diff*diff/expected; // fórmula del chi-cuadrado
        long adiff = counts[i] > expected ? (long)(counts[i]-expected) : (long)(expected-counts[i]);
        if(adiff>max_dev){ max_dev=adiff; max_pos=i; }
    }
    double avg_fixed = (double)total_fixed/TRIALS;

    printf("\n== %s ==\n", nombre);
    printf("Tiempo medio: %.2f us/barajado (%.3f s totales)\n", us_per_shuffle, secs);
    printf("Chi^2 (df=%d): %.2f  [ideal ~%.0f, >100 = sesgado]\n", N-1, chi2, (double)(N-1));
    printf("Max desviacion sobre esperado: %ld en posicion %d (esperado %.1f) [ideal <200]\n", max_dev, max_pos, expected);
    printf("Puntos fijos medios: %.3f (esperado ~1.0) [>2 = mal barajado]\n", avg_fixed);
}

int main(){
    // semillas distintas para evitar correlaciones
    srand(12345);
    evalua("40 swaps aleatorios", barajar_swaps);

    srand(67890);
    evalua("Fisher-Yates (39 swaps)", barajar_yates);
    return 0;
}
