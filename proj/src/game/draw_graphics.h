#include "imgs/tetromino_blue.xpm"
#include "imgs/tetromino_yellow.xpm"
#include "imgs/tetromino_red.xpm"
#include "imgs/tetromino_purple.xpm"
#include "imgs/tetromino_green.xpm"
#include "imgs/tetromino_cyan.xpm"
#include "imgs/tetromino_orange.xpm"
#include "imgs/clear.xpm"
#include "imgs/menu_800x600.xpm"
#include "imgs/font.xpm"
#include "imgs/cursor.xpm"
#include "imgs/empty_cursor.xpm"
#include "imgs/board.xpm"
#include "imgs/gradient.xpm"
#include "imgs/sidebar.xpm"
#include "imgs/square_resized.xpm"
#include "imgs/blank_menu.xpm"
#include "imgs/font_white.xpm"

#include "devices/video_card.h"

/**
 * @brief Loads all of the xpm images into memory, creating the xpm image object like struct
 * 
 * @return Returns 0 upon success and non-zero otherwise
 */
int load_xpms();

/**
 * @brief Loads a tetromino xpm into a tetromino
 * 
 * @param tetromino The tetromino currently being played
 */
void load_tetromino_image(tetromino_t *tetromino);

/**
 * @brief Draws the current board
 * 
 * @param board_state The current board
 */
void draw_board(tetromino_type board_state[16][10]);

/**
 * @brief Draws the board background
 * 
 */
void draw_board_bg();

/**
 * @brief Draws the main menu
 * 
 */
void draw_main_menu();

/**
 * @brief Draws the gradient in the background of the playing game state
 * 
 */
void draw_gradient();

/**
 * @brief Draws the leaderboard menu
 * 
 */
void draw_leaderboard_menu();

/**
 * @brief Draws the finished game menu
 * 
 */
void draw_finished_menu();

/**
 * @brief Draws a string starting in the x, y coordinate, scaling the font
 * 
 * @param string The string to be drawn
 * @param x The x coordinate of the cursor
 * @param y The y coordinate of the cursor
 * @param scale The scale of the font
 * @param white True to select the white font
 */
void draw_string(const char *string, uint16_t x, uint16_t y, uint8_t scale, bool white);

/**
 * @brief Draws a character starting in the x, y coordinate, scaling the font
 * 
 * @param character The character to be drawn
 * @param x The x coordinate of the cursor
 * @param y The y coordinate of the cursor
 * @param scale The scale of the font
 * @param white True to select the white font
 */
void draw_character(const char character, uint16_t x, uint16_t y, uint8_t scale, bool white);

/**
 * @brief Draws the player's current score
 * 
 * @param score The player's score
 */
void draw_score(char *score);

/**
 * @brief Swaps the "drawing"/"main" buffer with the "back" buffer
 * 
 */
void _swap_buffer();

/**
 * @brief Draws a cursor in the x, y position
 * 
 * @param x The x coordinate of the cursor
 * @param y The y coordinate of the cursor
 */
void draw_cursor(uint16_t x, uint16_t y);

/**
 * @brief Clears the cursor in the x, y position
 * 
 * @param x The x coordinate of the cursor
 * @param y The y coordinate of the cursor
 */
void erase_cursor(uint16_t x, uint16_t y);
