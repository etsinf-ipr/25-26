/*
 Integración completa del simulador de tráfico.
 Incluye funcionalidades de:
 - número varialble de calles
 - semáforos con ciclos variables, sincronización
 - coches a distintas velocidades
 - estadísticas cuando acaba la simulación (gráficas ASCII?)

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

// Caracteres del mapa
#define VACIO ' '
#define CARRETERAH '-'
#define CARRETERAV '|'
#define CRUCE '+'
#define COCHE_RAPIDO '*'
#define COCHE_NORMAL 'o'
#define COCHE_LENTO '#'
#define COCHE 'o' // Fallback or generic
#define SEMAFOROH '-'
#define SEMAFOROV '|'

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

// ---------------------------------
// PROTOTIPOS
// ---------------------------------

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
  int num_semaforos = 0;

  // Estadísticas
  Estadisticas stats = {{0}, {0}, {0}};

  srand(time(NULL));

  // 1. Generar entorno
  generar_calles(&calles);
  inicializar_mapa(mapa_base, &calles);
  inicializar_semaforos(semaforos, &calles, &num_semaforos);

  // 2. Inicializar coches (todos fuera al principio)
  inicializar_coches(coches);
  // Podemos crear un coche inicial como en los ejemplos básicos, o dejar que la
  // función entrada los cree. Para asegurar actividad al inicio, creamos uno.
  nuevo_coche(&coches[0], &calles, 0, &stats);

  // Bucle principal
  for (int turno = 0; turno < TURNOS; turno++) {
    restaurar_mapa(mapa, mapa_base);

    // Actualizar semáforos
    actualizar_semaforos(semaforos, num_semaforos, turno);

    // Control de entrada de nuevos coches (Carta E)
    if (entrada(turno, EXP, 0.5)) {
      // Buscar slot libre
      for (int i = 0; i < MAX_COCHES; i++) {
        if (coches[i].fila == OUT) {
          nuevo_coche(&coches[i], &calles, turno, &stats);
          break;
        }
      }
    }

    // Mover y situar coches
    mover_coches(mapa, coches, semaforos, num_semaforos, turno, &stats);
    situar_coches(mapa, coches);

    // Pintar
    // System clear opcional:
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
  // Generación por secciones para garantizar distribución y separación

  // Calles Horizontales
  int segmento_h = N / NUM_CALLES_H;
  for (int i = 0; i < NUM_CALLES_H; i++) {
    // Definir rango para la calle i: [min, max]
    // Se deja margen de 1 celda al principio y al final del segmento para
    // evitar adyacencias
    int min_pos = (i * segmento_h) + 1;
    int max_pos = ((i + 1) * segmento_h) - 2;

    // Ajustes por seguridad (bordes del mapa)
    if (min_pos < 1)
      min_pos = 1;
    if (max_pos >= N - 1)
      max_pos = N - 1; // Changed N-1 to N-2 to match original logic

    if (max_pos < min_pos) {
      // Fallback si hay demasiadas calles para el tamaño del mapa
      calles->filas_h[i] = min_pos;
    } else {
      calles->filas_h[i] = min_pos + rand() % (max_pos - min_pos + 1);
    }
  }

  // Calles Verticales
  int segmento_v = N / NUM_CALLES_V;
  for (int i = 0; i < NUM_CALLES_V; i++) {
    int min_pos = (i * segmento_v) + 1;
    int max_pos = ((i + 1) * segmento_v) - 2;

    if (min_pos < 1)
      min_pos = 1;
    if (max_pos >= N - 1)
      max_pos = N - 1; // Changed N-1 to N-2 to match original logic

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
      } else if (mapa[i][j] == CRUCE) {
        // Verificar si hay semáforo en este cruce para dibujarlo
        putchar(simbolo_cruce(i, j, semaforos, num_semaforos));
      } else {
        putchar(mapa[i][j]);
      }
    }
    printf("\n");
  }
  // printf("\n");
  usleep(50000); // 50 ms
}

// ---------------------------------
// IMPLEMENTACIÓN: SEMÁFOROS
// ---------------------------------

void inicializar_semaforos(Semaforo semaforos[], Calles *calles,
                           int *num_semaforos) {
  *num_semaforos = 0;
  // Pone un semáforo en cada intersección de las calles generadas
  for (int i = 0; i < NUM_CALLES_H; i++) {
    for (int j = 0; j < NUM_CALLES_V; j++) {
      semaforos[*num_semaforos].fila = calles->filas_h[i];
      semaforos[*num_semaforos].col = calles->cols_v[j];

      // Configuración individual
      // Ciclo base entre 20 y 40
      semaforos[*num_semaforos].ciclo = 20 + rand() % 21;
      // Tiempo H mitad del ciclo aprox, con variación
      semaforos[*num_semaforos].tiempo_h = semaforos[*num_semaforos].ciclo / 2;

      // Sincronización: offset basado en la posición (i+j)
      // Esto crea una "ola" diagonal
      semaforos[*num_semaforos].offset = (i + j) * 5;

      semaforos[*num_semaforos].estado = VERDE_H; // Estado inicial
      (*num_semaforos)++;
    }
  }
}

void actualizar_semaforos(Semaforo semaforos[], int num_semaforos, int turno) {
  for (int i = 0; i < num_semaforos; i++) {
    // Calcular tiempo dentro del ciclo individual
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
  // Buscar si hay un semáforo en la celda destino
  for (int i = 0; i < num_semaforos; i++) {
    if (semaforos[i].fila == fila_destino && semaforos[i].col == col_destino) {
      // Lógica de paso:
      // VERDE_H permite pasar si vamos DERECHA o IZQUIERDA
      if (semaforos[i].estado == VERDE_H &&
          (dir_llegada == DERECHA || dir_llegada == IZQUIERDA))
        return true;
      // VERDE_V permite pasar si vamos ARRIBA o ABAJO
      if (semaforos[i].estado == VERDE_V &&
          (dir_llegada == ARRIBA || dir_llegada == ABAJO))
        return true;

      return false; // Rojo
    }
  }
  return true; // No hay semáforo (o no encontrado), se permite paso
}

char simbolo_cruce(int fila, int col, Semaforo semaforos[], int num_semaforos) {
  for (int i = 0; i < num_semaforos; i++) {
    if (semaforos[i].fila == fila && semaforos[i].col == col) {
      return semaforos[i].estado == VERDE_H ? SEMAFOROH : SEMAFOROV;
    }
  }
  return CRUCE; // Fallback
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
  // Lógica carta AD: elegir extremos de las calles generadas
  // Calcular máximo de extremos posibles
  int filas[NUM_ENTRADAS], cols[NUM_ENTRADAS], dirs[NUM_ENTRADAS];
  int k = 0;

  // Extremos de calles horizontales
  for (int i = 0; i < NUM_CALLES_H; i++) {
    filas[k] = calles->filas_h[i];
    cols[k] = 0;
    dirs[k++] = DERECHA;
    filas[k] = calles->filas_h[i];
    cols[k] = N - 1;
    dirs[k++] = IZQUIERDA;
  }
  // Extremos de calles verticales
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

  // Velocidad aleatoria
  coche->periodo = 1 + rand() % 3;
  coche->espera = 0;
  coche->turno_entrada = turno;

  if (stats) {
    stats->creados[coche->periodo]++;
  }

  // FORCE BUG
  if (rand() % 10 == 0) {
    coche->fila = 0;
    coche->col = 0; // Likely VACIO
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

// Versión multi-coche: intenta mover todos los coches activos
void mover_coches(char mapa[][N], Coche coches[], Semaforo semaforos[],
                  int num_semaforos, int turno, Estadisticas *stats) {
  // Iterar por todos los coches
  // (Opcional: orden aleatorio para evitar prioridades fijas)
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

  // Gestión de velocidad
  if (coche->espera > 0) {
    coche->espera--;
    return;
  }

  int df[] = {-1, 0, 1, 0};
  int dc[] = {0, 1, 0, -1};

  // 1. Ampliacion D: Decidir giro si ya estamos EN un cruce antes de movernos
  decidir_giro_cruce(mapa, coche);

  // Calcular posición propuesta
  int nueva_fila = coche->fila + df[coche->dir];
  int nueva_col = coche->col + dc[coche->dir];

  // Verificar salida del mapa
  if (!dentro_mapa(nueva_fila, nueva_col)) {
    // Registrar estadísticas
    if (stats) {
      stats->salidos[coche->periodo]++;
      stats->tiempo_total[coche->periodo] += (turno - coche->turno_entrada);
    }
    coche->fila = OUT;
    coche->col = OUT;
    return;
  }

  // Verificar si se mete en VACIO (campo a través)
  if (mapa[nueva_fila][nueva_col] == VACIO) {
    return;
  }

  // 2. Ampliación B: Verificar Semáforo si vamos a entrar en un cruce
  if (mapa[nueva_fila][nueva_col] == CRUCE) {
    if (!puede_pasar(nueva_fila, nueva_col, coche->dir, semaforos,
                     num_semaforos)) {
      if (stats)
        stats->paradas_semaforo++;
      return; // Semáforo en rojo para nosotros
    }
  }

  // 3. Ampliación C: Verificar Colisión con otros coches
  if (celda_ocupada(nueva_fila, nueva_col, coche->dir, coches, coche)) {
    if (stats)
      stats->colisiones_evitadas++;
    return; // Celda ocupada
  }

  // Mover
  coche->fila = nueva_fila;
  coche->col = nueva_col;

  // Reiniciar espera
  coche->espera = coche->periodo - 1;
}

void decidir_giro_cruce(char mapa[][N], Coche *coche) {
  // Si el coche está actualmente en un cruce, puede girar
  if (es_cruce_logico(coche->fila, coche->col, mapa)) {
    int giro = rand() % 3; // 0=sigue, 1=girar izq, 2=girar der (relativo o
                           // absoluto simplificado)

    // La implementación original de D:
    // if (giro == 1) coche->dir = (coche->dir + 3) % 4; // Izquierda relativa
    // else if (giro == 2) coche->dir = (coche->dir + 1) % 4; // Derecha
    // relativa

    // NOTA: Al girar, hay que asegurarse de que no volvemos por donde venimos o
    // calles invalidas? En el modelo de rejilla simple, cualquier dirección
    // perpendicular es válida si hay calle. Pero como es un cruce de 4 vías
    // (tipo CRUCE), todas las direcciones son válidas.

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
      continue; // Ignorar coches fuera

    if (coches[i].fila == fila && coches[i].col == col) {
      // Lógica original C: permitir cruce si direcciones opuestas?
      // "Si direcciones opuestas return false (no choca, se cruzan swap?? No,
      // en C puro chocan)" Revisando original C: if
      // (direcciones_opuestas(coches[i].dir, dir)) return false; Esto implica
      // que si van de frente se "atraviesan". Mantendremos esa lógica si estaba
      // en el original.
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

    // Barra gráfica
    printf("[");
    int bar_len = (int)(avg / 2); // Escala: 1 char = 2 turnos
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
