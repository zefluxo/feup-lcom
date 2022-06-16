#include "logic.h"

tetromino_type tmp;
int piece_count = 7;

void shuffle(tetromino_type* array) {
    for (int i = 6; i > 0; i--) {
        srand(time(NULL));
        int j = rand() % i;
        tmp = array[j];
        array[j] = array[i];
        array[i] = tmp;
    }
    for (int i = 6; i > 0; i--) {
        srand(time(NULL));
        int j = rand() % i;
        tmp = array[j];
        array[j] = array[i];
        array[i] = tmp;
    }
}
