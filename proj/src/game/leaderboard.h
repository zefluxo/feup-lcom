#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "game_state.h"
#include "../devices/rtc.h"

/**
 * @brief Dynamic array struct for handling leaderboard entries
 * 
 */

typedef struct {
  char* name;
  char* score;
  char* date;
} Entry;

typedef struct {
    Entry* array;
    size_t used;
    size_t size;
} Array;

extern Array scores;
extern char name[4];
extern int name_len;

/**
 * @brief Initialize a leaderboard array
 * 
 * @param the array to be initialized
 * @param initial size of the array
 */
void init_array(Array* a, size_t init_size);

/**
 * @brief Insert element into array
 * 
 * @param the array to insert to
 * @param element to be inserted
 */
void insert_array(Array* a, Entry element);

/**
 * @brief Free created array
 * 
 * @param the array to be freed
 */
void free_array(Array* a);

//-------------------------------------------------------------------

/**
 * @brief Get scores from the saved leaderboard
 * 
 */
void get_scores();

/**
 * @brief Output leaderboard scores to screen
 * 
 */
void draw_scores();

/**
 * @brief Get current player's leaderboard entry 
 * 
 */
void get_player_entry();

/**
 * @brief Draw the input of the user's name
 * 
 */
void draw_player_name();

/**
 * @brief Comparator function for entries (descending order)
 * 
 * @param entry
 * @param entry
 * @return int
 */
int entry_compare(const void* s1, const void* s2);

/**
 * @brief Sort the leaderboard by player scores
 * 
 */
void sort_scores();

/**
 * @brief Save the leaderboard in memory to the leaderboard file
 * 
 */
void save_leaderboard();

/**
 * @brief Clean-up function to free the leaderboard on exit
 * 
 */
void lb_clean_up();
