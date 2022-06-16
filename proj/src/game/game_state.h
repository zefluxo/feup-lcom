#pragma once

#include "draw_graphics.h"
#include "logic.h"
#include "utils.h"
#include "leaderboard.h"

/**
 * @brief The current state of the game, determines what is displayed and the overall behaviour of the program
 * 
 */
typedef enum {
  PLAYING,
  MAIN_MENU,
  FINISHED,
  LEADERBOARD,
  EXIT
} game_state;

/**
 * @brief The direction of the collision to be checked
 * 
 */
typedef enum {
  DOWN,
  LEFT,
  RIGHT,
  NO_DIR
} collision_dir;

/**
 * @brief The direction of rotation
 * 
 */
typedef enum {
  R_LEFT,
  R_RIGHT
} rotate_dir;

/**
 * @brief The x, y position of a certain element (cursor and leaderboard contents)
 * 
 */
typedef struct {
  uint16_t x;
  uint16_t y;
} Position;

static tetromino_type board[16][10];
static tetromino_t *tetromino;
extern game_state state;
static uint8_t time_score;

/**
 * @brief Draws the main menu
 * 
 */
void _main_menu();

/**
 * @brief Starts the game, draws the ui components, prepares the board and sets other variables needed to run the game
 * 
 */
void start_game();

/**
 * @brief Draws the leaderboard menu
 * 
 */
void _leaderboard_menu();

/**
 * @brief Draws the scores in the leaderboard menu
 * 
 */
void draw_scores();

/**
 * @brief Draws the IO components of the game
 * 
 */
void draw_game_ui();

/**
 * @brief Attempts to move a piece to the left
 * 
 */
void move_piece_left();

/**
 * @brief Attempts to move a piece to the right
 * 
 */
void move_piece_right();

/**
 * @brief Draws the post game menu
 * 
 */
void _finished_menu();

/**
 * @brief Draws the current board
 * 
 */
void _draw_board();

/**
 * @brief Draws the player's score
 * 
 */
void _draw_score();

/**
 * @brief Piece falling logic
 * 
 */
void piece_fall();

/**
 * @brief Clears a tetromino from the board
 * 
 */
void clear_tetromino();

/**
 * @brief Places a tetromino on the board
 * 
 */
void place_tetromino();

/**
 * @brief Checks for collisions of a piece in a certain direction
 * 
 * @param dir The dierction of the piece movement
 * @return Returns true if a collision was detected
 */
bool check_collision(collision_dir dir);

/**
 * @brief Rotates a piece in a given direction
 * 
 * @param rotation The direction of rotation
 */
void piece_rotate(rotate_dir rotation);

/**
 * @brief Updates the cursor position
 * 
 * @param x_val The x amount of displacement in the x axis
 * @param y_val The y amount of displacement in the y axis
 */
void update_cursor(uint16_t x_val, uint16_t y_val);

/**
 * @brief Moves a piece in the x axis
 * 
 * @param x_displacement The amount of movement in the x axis
 */
void move_tetromino(uint16_t x_displacement);

/**
 * @brief Quickly drops a piece until its' first contact
 * 
 */
void hard_drop();

/**
 * @brief Draws the cursor
 * 
 */
void cursor_draw();

/**
 * @brief Clears the cursor
 * 
 */
void cursor_erase();

/**
 * @brief Verifies if mouse clicks are within certain values, used in the main menu
 * 
 */
void check_mouse_clicks();
int get_final_score();
