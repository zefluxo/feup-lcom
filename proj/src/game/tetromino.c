#include "tetromino.h"

void check_rotate_inside_border(tetromino_t* tetromino) {
  int iter;  
  if (tetromino->type == I || tetromino->type == O) iter = 4;
  else iter = 3;

  for (int i = 0; i < iter; i++)
    for (int j = 0; j < iter; j++) {
      if (tetromino->matrix[i][j] != 0 && tetromino->x + j > 9) {
        (tetromino->x)-= ((tetromino->x + j)-9);
      }
      if (tetromino->matrix[i][j] != 0 && tetromino->x + j < 0) {
        (tetromino->x)+= (0-(tetromino->x + j));
      }
    }
}


void rotatePieceLeft(tetromino_t* piece){
    if (piece->type == I || piece->type == O){
        rotateLeft(piece->matrix, 4, 4);
    } else {
        rotateLeft(piece->matrix, 3, 3);  
    } 
    check_rotate_inside_border(piece);
}

void rotatePieceRight(tetromino_t* piece){
    if (piece->type == I || piece->type == O) {
        rotateRight(piece->matrix, 4, 4);
    } else {
        rotateRight(piece->matrix, 3, 3);
    } 
    check_rotate_inside_border(piece);
}

tetromino_t* create_tetromino(tetromino_type type){
    tetromino_t *tetromino = (tetromino_t*) malloc(sizeof(tetromino_t));
    (type == O) ? (tetromino->x = 2) : (tetromino->x = 4);
    tetromino->y = 0;
    tetromino->type = type;

    if (type == I || type == O){
        tetromino->matrix = (uint8_t**) malloc(4*sizeof(uint8_t*));
        for (int i = 0; i < 4; i++){
            tetromino->matrix[i] = (uint8_t*) malloc(4*sizeof(uint8_t));
            memset(tetromino->matrix[i], 0, 4);
        }
    }
    else{
        tetromino->matrix = (uint8_t**) malloc(3*sizeof(uint8_t*));
        for (int i = 0; i < 3; i++){
            tetromino->matrix[i] = (uint8_t*) malloc(3*sizeof(uint8_t));
            memset(tetromino->matrix[i], 0, 3);
        }
    }
    

    switch(type){
        case I:
            tetromino->matrix[0][1] = 1;
            tetromino->matrix[1][1] = 1;
            tetromino->matrix[2][1] = 1;
            tetromino->matrix[3][1] = 1;
            break;
        case J:
            tetromino->matrix[0][1] = 1;
            tetromino->matrix[1][1] = 1;
            tetromino->matrix[2][1] = 1;
            tetromino->matrix[2][0] = 1;
            break;
        case L:
            tetromino->matrix[0][1] = 1;
            tetromino->matrix[1][1] = 1;
            tetromino->matrix[2][1] = 1;
            tetromino->matrix[2][2] = 1;
            break;
        case S:
            tetromino->matrix[1][1] = 1;
            tetromino->matrix[1][2] = 1;
            tetromino->matrix[2][0] = 1;
            tetromino->matrix[2][1] = 1;
            break;
        case O:
            tetromino->matrix[1][2] = 1;
            tetromino->matrix[1][1] = 1;
            tetromino->matrix[2][2] = 1;
            tetromino->matrix[2][1] = 1;
            break;
        case T:
            tetromino->matrix[1][0] = 1;
            tetromino->matrix[1][1] = 1;
            tetromino->matrix[1][2] = 1;
            tetromino->matrix[2][1] = 1;
            break;
        case Z:
            tetromino->matrix[1][0] = 1;
            tetromino->matrix[1][1] = 1;
            tetromino->matrix[2][1] = 1;
            tetromino->matrix[2][2] = 1;
            break;
        case CLEAR:
            break;
    }

    return tetromino;
}

void delete_tetromino(tetromino_t * tetromino){
    free(tetromino->matrix[0]);
    free(tetromino->matrix[1]);
    free(tetromino->matrix[2]);
    if (tetromino->type == I || tetromino->type == O) free (tetromino->matrix[3]);
    free(tetromino->matrix);
    free(tetromino);
}
