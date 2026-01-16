/*
    Implementación del juego 2048 en C
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#define SIZE 4
#define TARGET 2048

void init_board(int board[SIZE][SIZE]);
int add_random_tile(int board[][SIZE]);
int mover(int board[][SIZE], char direction);
void print(int board[][SIZE]);


void init_board(int board[SIZE][SIZE]) {
    srand(time(NULL));
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
    // Añadir dos números iniciales
    add_random_tile(board);
    add_random_tile(board);
    print(board);
}


int add_random_tile(int board[][SIZE]) {
    int vacia[SIZE * SIZE];
    int vid = 0;

    // Encontrar todas las posiciones vacías
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                vacia[vid++] = i * SIZE + j;
            }
        }
    }
    if (vid == 0) return 0; // No hay espacio para añadir un nuevo número
    // Seleccionar una posición aleatoria
    int sel = rand() % vid;
    int row = vacia[sel] / SIZE;
    int col = vacia[sel] % SIZE;
    // Añadir un 2
    board[row][col] = 2;
    return 1;
}

int mover_izquierda(int board[][SIZE]) {
    int changed = 0;
    for (int i = 0; i < SIZE; i++) {
        int last_merge_pos = -1;
        for (int j = 1; j < SIZE; j++) {
            if (board[i][j] == 0) continue;
            int k = j;
            while (k > 0 && board[i][k - 1] == 0) {
                board[i][k - 1] = board[i][k];
                board[i][k] = 0;
                k--;
                changed = 1;
            }
            if (k > 0 && board[i][k - 1] == board[i][k] && last_merge_pos != k - 1) {
                board[i][k - 1] *= 2;
                board[i][k] = 0;
                last_merge_pos = k - 1;
                changed = 1;
            }
        }
    }
    return changed;
}

int mover_derecha(int board[][SIZE]) {
    int changed = 0;
    for (int i = 0; i < SIZE; i++) {
        int last_merge_pos = SIZE;
        for (int j = SIZE - 2; j >= 0; j--) {
            if (board[i][j] == 0) continue;
            int k = j;
            while (k < SIZE - 1 && board[i][k + 1] == 0) {
                board[i][k + 1] = board[i][k];
                board[i][k] = 0;
                k++;
                changed = 1;
            }
            if (k < SIZE - 1 && board[i][k + 1] == board[i][k] && last_merge_pos != k + 1) {
                board[i][k + 1] *= 2;
                board[i][k] = 0;
                last_merge_pos = k + 1;
                changed = 1;
            }
        }
    }
    return changed;
}

int mover_arriba(int board[][SIZE]) {
    int changed = 0;
    for (int j = 0; j < SIZE; j++) {
        int last_merge_pos = -1;
        for (int i = 1; i < SIZE; i++) {
            if (board[i][j] == 0) continue;
            int k = i;
            while (k > 0 && board[k - 1][j] == 0) {
                board[k - 1][j] = board[k][j];
                board[k][j] = 0;
                k--;
                changed = 1;
            }
            if (k > 0 && board[k - 1][j] == board[k][j] && last_merge_pos != k - 1) {
                board[k - 1][j] *= 2;
                board[k][j] = 0;
                last_merge_pos = k - 1;
                changed = 1;
            }
        }
    }
    return changed;
}

int mover_abajo(int board[][SIZE]) {
    int changed = 0;
    for (int j = 0; j < SIZE; j++) {
        int last_merge_pos = SIZE;
        for (int i = SIZE - 2; i >= 0; i--) {
            if (board[i][j] == 0) continue;
            int k = i;
            while (k < SIZE - 1 && board[k + 1][j] == 0) {
                board[k + 1][j] = board[k][j];
                board[k][j] = 0;
                k++;
                changed = 1;
            }
            if (k < SIZE - 1 && board[k + 1][j] == board[k][j] && last_merge_pos != k + 1) {
                board[k + 1][j] *= 2;
                board[k][j] = 0;
                last_merge_pos = k + 1;
                changed = 1;
            }
        }
    }
    return changed;
}


int mover(int board[][SIZE], char direction) {
    int changed = 0;
    switch(direction) {
        case 'w': changed = mover_arriba(board); break; 
        case 's': changed = mover_abajo(board); break; 
        case 'a': changed = mover_izquierda(board); break; 
        case 'd': changed = mover_derecha(board); break; 
        case 'q': exit(0); break;
    }
    return changed;
}

void print(int board[][SIZE]) {
    system("clear"); 
    printf("2048 Game Board:\n");
    printf("-----------------\n");
    printf("w: arriba, s: abajo, a: izda, d: dcha, q: salir\n\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%4d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void disable_canonical_mode() {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~ICANON;  // Desactivar modo canonical
    tty.c_lflag &= ~ECHO;    // Desactivar echo
    tty.c_cc[VMIN] = 1;      // Esperar al menos 1 byte
    tty.c_cc[VTIME] = 0;     // Sin timeout
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void enable_canonical_mode() {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= ICANON;   // Activar modo canonical
    tty.c_lflag |= ECHO;     // Activar echo
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}




int main() {
    int board[SIZE][SIZE];
    init_board(board);
    disable_canonical_mode();
    int space = 1;
    while(space > 0){
        char c = getchar(); // Leer sin necesidad de Enter
        if (c != EOF && c != '\n') {
            if (mover(board, c)) {
                space = add_random_tile(board);
                print(board);
            }
        }
    }
    enable_canonical_mode();
    return 0;
}