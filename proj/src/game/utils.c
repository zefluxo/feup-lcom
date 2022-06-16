#include "utils.h"

void reverseColumns(uint8_t **arr, unsigned R, unsigned C)
{
    for (unsigned i = 0; i < C; i++){
        for (unsigned j = 0, k = C - 1; j < k; j++, k--){
            uint8_t temp = arr[j][i];
            arr[j][i] = arr[k][i];
            arr[k][i] = temp;
        } 
    }
}

void reverseRows(uint8_t **arr, unsigned R, unsigned C)
{
    for (unsigned i = 0; i < R; i++){
        for (unsigned j = 0, k = R - 1; j < k; j++, k--){
            uint8_t temp = arr[i][j];
            arr[i][j] = arr[i][k];
            arr[i][k] = temp;
        } 
    }
}

void transpose(uint8_t **arr, unsigned R, unsigned C)
{
    for (unsigned i = 0; i < R; i++){
        for (unsigned j = i; j < C; j++){
            uint8_t temp = arr[i][j];
            arr[i][j] = arr[j][i];
            arr[j][i] = temp;
        }
    }
}
 
void printMatrix(uint8_t **arr, unsigned R, unsigned C)
{
    for (unsigned i = 0; i < R; i++) {
        for (unsigned j = 0; j < C; j++)
            printf("%d ", arr[j][i]);
        printf("\n");
    }
}

void rotateLeft(uint8_t **arr, unsigned R, unsigned C)
{
    transpose(arr, R, C);
    reverseColumns(arr, R, C);
}

void rotateRight(uint8_t **arr, unsigned R, unsigned C)
{
    transpose(arr, R, C);
    reverseRows(arr, R, C);
}

bool is_alpha(char character) {
    if ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z'))
        return true;

    return false;
}

void get_keys() {

    memset(keys, 0, sizeof(keys));

    keys[A_KEY] = 'A';
    keys[B_KEY] = 'B';
    keys[C_KEY] = 'C';
    keys[D_KEY] = 'D';
    keys[E_KEY] = 'E';
    keys[F_KEY] = 'F';
    keys[G_KEY] = 'G';
    keys[H_KEY] = 'H';
    keys[I_KEY] = 'I';
    keys[J_KEY] = 'J';
    keys[K_KEY] = 'K';
    keys[L_KEY] = 'L';
    keys[M_KEY] = 'M';
    keys[N_KEY] = 'N';
    keys[O_KEY] = 'O';
    keys[P_KEY] = 'P';
    keys[Q_KEY] = 'Q';
    keys[R_KEY] = 'R';
    keys[S_KEY] = 'S';
    keys[T_KEY] = 'T';
    keys[U_KEY] = 'U';
    keys[V_KEY] = 'V';
    keys[W_KEY] = 'W';
    keys[X_KEY] = 'X';
    keys[Y_KEY] = 'Y';
    keys[Z_KEY] = 'Z';
}
