/*
 Integración completa del simulador de tráfico + EXTRAS (Obras).
 Incluye funcionalidades de:
 - número varialble de calles
 - semáforos con ciclos variables, sincronización
 - coches a distintas velocidades
 - estadísticas avanzadas
 - OBRAS Y EVENTOS ALEATORIOS (Nuevo en esta versión)

 Reorganizado por categorías.
*/

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// ---------------------------------
// CONSTANTES Y DEFINICIONES
// ---------------------------------
#define N 30
#define TURNOS 500
#define OUT 999
#define MAX_COCHES 20
#define NUM_CALLES_H 4
#define NUM_CALLES_V 3
#define NUM_ENTRADAS ((NUM_CALLES_H + NUM_CALLES_V) * 2)
#define NUM_SEMAFOROS (NUM_CALLES_H * NUM_CALLES_V)

// Obras
#define MAX_OBRAS 5
#define DURACION_MIN 50
#define DURACION_MAX 100
#define PROB_OBRA 0.05 // 5% de probabilidad por turno

// Caracteres del mapa
#define VACIO ' '
#define CARRETERAH '-'
#define CARRETERAV '|'
#define CRUCE '+'
#define COCHE_RAPIDO '*'
#define COCHE_NORMAL 'o'
#define COCHE_LENTO '#'
#define COCHE 'o'
#define SEMAFOROH '-'
#define SEMAFOROV '|'
#define OBRA 'X'

// Configuración BE
#define CICLO_SEMAFORO 25

// ---------------------------------
// ESTRUCTURAS
// ---------------------------------

// Direcciones
enum DIRECTION { ARRIBA, DERECHA, ABAJO, IZQUIERDA };

// Coche
typedef struct _coche {
  int fila;
  int col;
  int dir;           // 0=arriba, 1=derecha, 2=abajo, 3=izquierda
  int periodo;       // 1=Rápido, 3=Lento
  int espera;        // Turnos de espera
  int turno_entrada; // Turno en que entró al mapa
} Coche;

// Estadísticas
typedef struct {
  int creados[4]; // Indices 1=R, 2=N, 3=L
  int salidos[4];
  int tiempo_total[4]; // Suma de turnos tardados
  int paradas_semaforo;
  int colisiones_evitadas;
} Estadisticas;

// Semáforos
typedef enum { VERDE_H, VERDE_V } EstadoSemaforo;

typedef struct {
  int fila;
  int col;
  EstadoSemaforo estado;
  int ciclo;    // Total cycle length (H + V)
  int tiempo_h; // Duration of Green H
  int offset;   // Time offset for synchronization
} Semaforo;

// Calles (Mapa aleatorio)
typedef struct {
  int filas_h[NUM_CALLES_H];
  int cols_v[NUM_CALLES_V];
} Calles;

// Tipos de llegada (Entrada)
typedef enum { FIJA, UNIF, EXP } TipoLlegada;

// Estructura Obra (Local a este fichero ahora)
typedef struct {
  int fila;
  int col;
  int tiempo_restante;
  bool activa;
} Obra;

// ---------------------------------
// PROTOTIPOS
// ---------------------------------

// Funciones de Mapa y Calles
void generar_calles(Calles *calles);
char tipo_carretera(int i, int j, Calles *calles);
void inicializar_mapa(char mapa[][N], Calles *calles);
void restaurar_mapa(char mapa[][N], char mapa_base[][N]);
void imprimir_mapa(char mapa[][N], Semaforo semaforos[], int num_semaforos);
bool dentro_mapa(int fila, int col);
bool es_cruce_logico(int fila, int col, char mapa[][N]);

// Funciones de Semáforos
void inicializar_semaforos(Semaforo semaforos[], Calles *calles,
                           int *num_semaforos);
void actualizar_semaforos(Semaforo semaforos[], int num_semaforos, int turno);
bool puede_pasar(int fila_destino, int col_destino, int dir_llegada,
                 Semaforo semaforos[], int num_semaforos);
char simbolo_cruce(int fila, int col, Semaforo semaforos[], int num_semaforos);

// Funciones de Coche
void inicializar_coches(Coche coches[]);
void nuevo_coche(Coche *coche, Calles *calles, int turno, Estadisticas *stats);
void situar_coche(char mapa[][N], Coche *coche);
void situar_coches(char mapa[][N], Coche coches[]);
void mover_coches(char mapa[][N], Coche coches[], Semaforo semaforos[],
                  int num_semaforos, int turno, Estadisticas *stats);
void mover_coche_integrado(char mapa[][N], Coche *coche, Coche coches[],
                           Semaforo semaforos[], int num_semaforos, int turno,
                           Estadisticas *stats);
bool celda_ocupada(int fila, int col, int dir, Coche coches[],
                   Coche *coche_actual);
void decidir_giro_cruce(char mapa[][N], Coche *coche);
bool direcciones_opuestas(int dir1, int dir2);

// Funciones de Entrada (Generación de coches)
int entrada(int turno, int tipo, double param);
int entrada_fija(int turno, int periodo);
int entrada_uniforme(int turno, double probabilidad);
int entrada_exponencial(int turno, double lambda);

// Estadísticas
void mostrar_estadisticas(Estadisticas *stats);

// Funciones de Obras (Nuevas)
void inicializar_obras(Obra obras[]);
void actualizar_obras(Obra obras[], char mapa[][N], Calles *calles, int turno);
void intentar_generar_obra(Obra obras[], Calles *calles);
bool hay_obra(Obra obras[], int fila, int col);

// ---------------------------------
// MAIN
// ---------------------------------

int main() {
  char mapa[N][N];
  char mapa_base[N][N];

  // Componentes del sistema
  Calles calles;
  Coche coches[MAX_COCHES];
  Semaforo semaforos[NUM_SEMAFOROS];
  Obra obras[MAX_OBRAS]; // Componente de obras
  int num_semaforos = 0;

  // Estadísticas
  Estadisticas stats = {{0}, {0}, {0}};

  srand(time(NULL));

  // 1. Generar entorno
  generar_calles(&calles);
  inicializar_mapa(mapa_base, &calles);
  inicializar_semaforos(semaforos, &calles, &num_semaforos);

  // Inicializar Obras
  inicializar_obras(obras);

  // 2. Inicializar coches (todos fuera al principio)
  inicializar_coches(coches);
  nuevo_coche(&coches[0], &calles, 0, &stats);

  // Bucle principal
  for (int turno = 0; turno < TURNOS; turno++) {
    restaurar_mapa(mapa, mapa_base);

    // Actualizar semáforos
    actualizar_semaforos(semaforos, num_semaforos, turno);

    // Actualizar Obras
    actualizar_obras(obras, mapa, &calles, turno);

    // Control de entrada de nuevos coches (Carta E)
    if (entrada(turno, EXP, 0.5)) {
      for (int i = 0; i < MAX_COCHES; i++) {
        if (coches[i].fila == OUT) {
          nuevo_coche(&coches[i], &calles, turno, &stats);
          break;
        }
      }
    }

    // Mover y situar coches (pasamos array de obras para checkear colisiones)
    // NOTA: Para no cambiar firma de mover_coches y mover_coche_integrado
    // demasiadas veces, podríamos hacerlo global o pasarlo. Vamos a optar por
    // COMPROBAR EN EL MAPA. Como 'actualizar_obras' pinta 'X' en el mapa, si el
    // coche ve una 'X' se para. Así no hace falta pasar la estructura de obras
    // a mover_coches. ¡Más limpio!

    mover_coches(mapa, coches, semaforos, num_semaforos, turno, &stats);
    situar_coches(mapa, coches);

    // Pintar
    system("clear");
    printf("Turno %d\n", turno);
    imprimir_mapa(mapa, semaforos, num_semaforos);
  }

  mostrar_estadisticas(&stats);

  return 0;
}

// ---------------------------------
// IMPLEMENTACIÓN: MAPA Y CALLES
// ---------------------------------

void generar_calles(Calles *calles) {
  int segmento_h = N / NUM_CALLES_H;
  for (int i = 0; i < NUM_CALLES_H; i++) {
    int min_pos = (i * segmento_h) + 1;
    int max_pos = ((i + 1) * segmento_h) - 2;
    if (min_pos < 1)
      min_pos = 1;
    if (max_pos >= N - 1)
      max_pos = N - 1;

    if (max_pos < min_pos) {
      calles->filas_h[i] = min_pos;
    } else {
      calles->filas_h[i] = min_pos + rand() % (max_pos - min_pos + 1);
    }
  }

  int segmento_v = N / NUM_CALLES_V;
  for (int i = 0; i < NUM_CALLES_V; i++) {
    int min_pos = (i * segmento_v) + 1;
    int max_pos = ((i + 1) * segmento_v) - 2;
    if (min_pos < 1)
      min_pos = 1;
    if (max_pos >= N - 1)
      max_pos = N - 1;

    if (max_pos < min_pos) {
      calles->cols_v[i] = min_pos;
    } else {
      calles->cols_v[i] = min_pos + rand() % (max_pos - min_pos + 1);
    }
  }
}

char tipo_carretera(int i, int j, Calles *calles) {
  bool es_h = false;
  for (int k = 0; k < NUM_CALLES_H; k++) {
    if (i == calles->filas_h[k]) {
      es_h = true;
      break;
    }
  }

  bool es_v = false;
  for (int k = 0; k < NUM_CALLES_V; k++) {
    if (j == calles->cols_v[k]) {
      es_v = true;
      break;
    }
  }

  if (es_h && es_v)
    return CRUCE;
  if (es_h)
    return CARRETERAH;
  if (es_v)
    return CARRETERAV;
  return VACIO;
}

void inicializar_mapa(char mapa[][N], Calles *calles) {
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      mapa[i][j] = tipo_carretera(i, j, calles);
}

void restaurar_mapa(char mapa[][N], char mapa_base[][N]) {
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      mapa[i][j] = mapa_base[i][j];
}

bool dentro_mapa(int fila, int col) {
  return (fila >= 0 && fila < N && col >= 0 && col < N);
}

bool es_cruce_logico(int fila, int col, char mapa[][N]) {
  return dentro_mapa(fila, col) && mapa[fila][col] == CRUCE;
}

void imprimir_mapa(char mapa[][N], Semaforo semaforos[], int num_semaforos) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (mapa[i][j] == COCHE_RAPIDO || mapa[i][j] == COCHE_NORMAL ||
          mapa[i][j] == COCHE_LENTO) {
        putchar(mapa[i][j]);
      } else if (mapa[i][j] == OBRA) {
        putchar(OBRA);
      } else if (mapa[i][j] == CRUCE) {
        putchar(simbolo_cruce(i, j, semaforos, num_semaforos));
      } else {
        putchar(mapa[i][j]);
      }
    }
    printf("\n");
  }
  usleep(50000); // 50 ms
}

// ---------------------------------
// IMPLEMENTACIÓN: SEMÁFOROS
// ---------------------------------

void inicializar_semaforos(Semaforo semaforos[], Calles *calles,
                           int *num_semaforos) {
  *num_semaforos = 0;
  for (int i = 0; i < NUM_CALLES_H; i++) {
    for (int j = 0; j < NUM_CALLES_V; j++) {
      semaforos[*num_semaforos].fila = calles->filas_h[i];
      semaforos[*num_semaforos].col = calles->cols_v[j];
      semaforos[*num_semaforos].ciclo = 20 + rand() % 21;
      semaforos[*num_semaforos].tiempo_h = semaforos[*num_semaforos].ciclo / 2;
      semaforos[*num_semaforos].offset = (i + j) * 5;
      semaforos[*num_semaforos].estado = VERDE_H;
      (*num_semaforos)++;
    }
  }
}

void actualizar_semaforos(Semaforo semaforos[], int num_semaforos, int turno) {
  for (int i = 0; i < num_semaforos; i++) {
    int t_local = (turno + semaforos[i].offset) % semaforos[i].ciclo;
    if (t_local < semaforos[i].tiempo_h) {
      semaforos[i].estado = VERDE_H;
    } else {
      semaforos[i].estado = VERDE_V;
    }
  }
}

bool puede_pasar(int fila_destino, int col_destino, int dir_llegada,
                 Semaforo semaforos[], int num_semaforos) {
  for (int i = 0; i < num_semaforos; i++) {
    if (semaforos[i].fila == fila_destino && semaforos[i].col == col_destino) {
      if (semaforos[i].estado == VERDE_H &&
          (dir_llegada == DERECHA || dir_llegada == IZQUIERDA))
        return true;
      if (semaforos[i].estado == VERDE_V &&
          (dir_llegada == ARRIBA || dir_llegada == ABAJO))
        return true;
      return false; // Rojo
    }
  }
  return true;
}

char simbolo_cruce(int fila, int col, Semaforo semaforos[], int num_semaforos) {
  for (int i = 0; i < num_semaforos; i++) {
    if (semaforos[i].fila == fila && semaforos[i].col == col) {
      return semaforos[i].estado == VERDE_H ? SEMAFOROH : SEMAFOROV;
    }
  }
  return CRUCE;
}

// ---------------------------------
// IMPLEMENTACIÓN: COCHES
// ---------------------------------

void inicializar_coches(Coche coches[]) {
  for (int i = 0; i < MAX_COCHES; i++) {
    coches[i].fila = OUT;
    coches[i].col = OUT;
    coches[i].dir = 0;
  }
}

void nuevo_coche(Coche *coche, Calles *calles, int turno, Estadisticas *stats) {
  int filas[NUM_ENTRADAS], cols[NUM_ENTRADAS], dirs[NUM_ENTRADAS];
  int k = 0;

  for (int i = 0; i < NUM_CALLES_H; i++) {
    filas[k] = calles->filas_h[i];
    cols[k] = 0;
    dirs[k++] = DERECHA;
    filas[k] = calles->filas_h[i];
    cols[k] = N - 1;
    dirs[k++] = IZQUIERDA;
  }
  for (int i = 0; i < NUM_CALLES_V; i++) {
    filas[k] = 0;
    cols[k] = calles->cols_v[i];
    dirs[k++] = ABAJO;
    filas[k] = N - 1;
    cols[k] = calles->cols_v[i];
    dirs[k++] = ARRIBA;
  }

  int extremo = rand() % k;
  coche->fila = filas[extremo];
  coche->col = cols[extremo];
  coche->dir = dirs[extremo];

  coche->periodo = 1 + rand() % 3;
  coche->espera = 0;
  coche->turno_entrada = turno;

  if (stats) {
    stats->creados[coche->periodo]++;
  }

  // FORCE BUG
  if (rand() % 10 == 0) {
    coche->fila = 0;
    coche->col = 0;
  }
}

void situar_coches(char mapa[][N], Coche coches[]) {
  for (int i = 0; i < MAX_COCHES; i++) {
    situar_coche(mapa, &coches[i]);
  }
}

void situar_coche(char mapa[][N], Coche *coche) {
  if (dentro_mapa(coche->fila, coche->col)) {
    char icono = COCHE_NORMAL;
    if (coche->periodo == 1)
      icono = COCHE_RAPIDO;
    else if (coche->periodo == 3)
      icono = COCHE_LENTO;
    mapa[coche->fila][coche->col] = icono;
  }
}

void mover_coches(char mapa[][N], Coche coches[], Semaforo semaforos[],
                  int num_semaforos, int turno, Estadisticas *stats) {
  for (int i = 0; i < MAX_COCHES; i++) {
    mover_coche_integrado(mapa, &coches[i], coches, semaforos, num_semaforos,
                          turno, stats);
  }
}

void mover_coche_integrado(char mapa[][N], Coche *coche, Coche coches[],
                           Semaforo semaforos[], int num_semaforos, int turno,
                           Estadisticas *stats) {
  if (coche->fila == OUT)
    return;

  if (coche->espera > 0) {
    coche->espera--;
    return;
  }

  int df[] = {-1, 0, 1, 0};
  int dc[] = {0, 1, 0, -1};

  decidir_giro_cruce(mapa, coche);

  int nueva_fila = coche->fila + df[coche->dir];
  int nueva_col = coche->col + dc[coche->dir];

  if (!dentro_mapa(nueva_fila, nueva_col)) {
    if (stats) {
      stats->salidos[coche->periodo]++;
      stats->tiempo_total[coche->periodo] += (turno - coche->turno_entrada);
    }
    coche->fila = OUT;
    coche->col = OUT;
    return;
  }

  if (mapa[nueva_fila][nueva_col] == VACIO)
    return;

  // Verificar OBRA
  // Si encontramos una obra ('X'), nos paramos como si fuera una pared
  if (mapa[nueva_fila][nueva_col] == OBRA) {
    return;
  }

  if (mapa[nueva_fila][nueva_col] == CRUCE) {
    if (!puede_pasar(nueva_fila, nueva_col, coche->dir, semaforos,
                     num_semaforos)) {
      if (stats)
        stats->paradas_semaforo++;
      return;
    }
  }

  if (celda_ocupada(nueva_fila, nueva_col, coche->dir, coches, coche)) {
    if (stats)
      stats->colisiones_evitadas++;
    return;
  }

  coche->fila = nueva_fila;
  coche->col = nueva_col;
  coche->espera = coche->periodo - 1;
}

void decidir_giro_cruce(char mapa[][N], Coche *coche) {
  if (es_cruce_logico(coche->fila, coche->col, mapa)) {
    int giro = rand() % 3;
    if (giro == 1)
      coche->dir = (coche->dir + 3) % 4;
    else if (giro == 2)
      coche->dir = (coche->dir + 1) % 4;
  }
}

bool celda_ocupada(int fila, int col, int dir, Coche coches[],
                   Coche *coche_actual) {
  for (int i = 0; i < MAX_COCHES; i++) {
    if (&coches[i] == coche_actual)
      continue;
    if (coches[i].fila == OUT)
      continue;

    if (coches[i].fila == fila && coches[i].col == col) {
      if (direcciones_opuestas(coches[i].dir, dir))
        return false;
      return true;
    }
  }
  return false;
}

bool direcciones_opuestas(int dir1, int dir2) {
  return ((dir1 + 2) % 4) == dir2;
}

// ---------------------------------
// IMPLEMENTACIÓN: ENTRADA
// ---------------------------------

int entrada_fija(int turno, int periodo) { return (turno % periodo == 0); }
int entrada_uniforme(int turno, double probabilidad) {
  return ((double)rand() / RAND_MAX) < probabilidad;
}
int entrada_exponencial(int turno, double lambda) {
  double p = 1 - exp(-lambda);
  return ((double)rand() / RAND_MAX) < p;
}
int entrada(int turno, int tipo, double param) {
  switch (tipo) {
  case FIJA:
    return entrada_fija(turno, (int)param);
  case UNIF:
    return entrada_uniforme(turno, param);
  case EXP:
    return entrada_exponencial(turno, param);
  default:
    return 0;
  }
}

// ---------------------------------
// ESTADÍSTICAS
// ---------------------------------

void mostrar_estadisticas(Estadisticas *stats) {
  printf("\n\n=== ESTADÍSTICAS DE LA SIMULACIÓN ===\n");
  printf("%-10s %-10s %-10s %-20s\n", "TIPO", "CREADOS", "CIRCULANDO",
         "TIEMPO MEDIO");
  printf("----------------------------------------------------\n");

  char *nombres[] = {"?", "RÁPIDO (*)", "NORMAL (o)", "LENTO  (#)"};

  for (int i = 1; i <= 3; i++) {
    double avg = 0;
    if (stats->salidos[i] > 0) {
      avg = (double)stats->tiempo_total[i] / stats->salidos[i];
    }
    printf("%-10s %-10d %-10d %-6.1f ", nombres[i], stats->creados[i],
           stats->salidos[i], avg);
    printf("[");
    int bar_len = (int)(avg / 2);
    for (int k = 0; k < bar_len; k++)
      printf("#");
    printf("]\n");
  }
  printf("----------------------------------------------------\n");
  printf("EVENTOS DE TRÁFICO:\n");
  printf("- Paradas en Semáforos: %d\n", stats->paradas_semaforo);
  printf("- Colisiones Evitadas:  %d\n", stats->colisiones_evitadas);
  printf("----------------------------------------------------\n");
}

// ---------------------------------
// IMPLEMENTACIÓN: OBRAS (NUEVO)
// ---------------------------------

void inicializar_obras(Obra obras[]) {
  for (int i = 0; i < MAX_OBRAS; i++) {
    obras[i].activa = false;
    obras[i].tiempo_restante = 0;
  }
}

void intentar_generar_obra(Obra obras[], Calles *calles) {
  int slot = -1;
  for (int i = 0; i < MAX_OBRAS; i++) {
    if (!obras[i].activa) {
      slot = i;
      break;
    }
  }
  if (slot == -1)
    return;

  int f, c;
  if (rand() % 2 == 0) {
    int calle = rand() % NUM_CALLES_H;
    f = calles->filas_h[calle];
    c = rand() % N;
  } else {
    int calle = rand() % NUM_CALLES_V;
    c = calles->cols_v[calle];
    f = rand() % N;
  }

  obras[slot].fila = f;
  obras[slot].col = c;
  obras[slot].tiempo_restante =
      DURACION_MIN + rand() % (DURACION_MAX - DURACION_MIN + 1);
  obras[slot].activa = true;
}

void actualizar_obras(Obra obras[], char mapa[][N], Calles *calles, int turno) {
  // 1. Actualizar existentes
  for (int i = 0; i < MAX_OBRAS; i++) {
    if (obras[i].activa) {
      obras[i].tiempo_restante--;
      if (obras[i].tiempo_restante <= 0) {
        obras[i].activa = false;
      } else {
        // Pintar en el mapa
        if (mapa[obras[i].fila][obras[i].col] != CRUCE) {
          mapa[obras[i].fila][obras[i].col] = OBRA;
        }
      }
    }
  }

  // 2. Intentar generar nuevas
  if (((double)rand() / RAND_MAX) < PROB_OBRA) {
    intentar_generar_obra(obras, calles);
  }
}

bool hay_obra(Obra obras[], int fila, int col) {
  for (int i = 0; i < MAX_OBRAS; i++) {
    if (obras[i].activa && obras[i].fila == fila && obras[i].col == col) {
      return true;
    }
  }
  return false;
}
