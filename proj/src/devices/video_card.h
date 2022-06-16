#pragma once

#include "game/tetromino.h"
#include "vc_defines.h"

#include <machine/int86.h>
#include <stdint.h>

/**
 * @brief Reads the current mode information, maps the virtual memory and chenges the graphics mode
 * 
 * @param mode The mode to be set, read and mapped
 * 
 * @return Returns the address to the base address of the "front buffer" on success and NULL otherwise
 */
void *(vg_init) (uint16_t mode);

/**
 * @brief Changes MINIX's graphic mode
 * 
 * @param mode The mode to be set
 * 
 * @return Returns 0 upon success and non-zero otherwise
 */
int(change_mode)(uint16_t mode);

/**
 * @brief Maps the virtual memory space in accord with the set graphics mode, creating 2 buffers for double buffering.
 * 
 * @return Returns 0 upon success and non-zero otherwise
 */
int(map_vm)();

/**
 * @brief Sets the color of the x, y pixel in the "back buffer"
 * 
 * @param x The x coordinate of the pixel on the screen
 * @param y The y coordinate of the pixel on the screen
 * @param color The color to be set for the pixel
 */
void(draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief Draws a xpm image, pixel by pixel, starting in x, y, in the "back buffer"
 * 
 * @param img The xpm image to be drawn
 * @param x The x cooridnate of the top left corner of the image
 * @param y The y cooridnate of the top left corner of the image
 */
void(draw_xpm)(xpm_image_t img, uint16_t x, uint16_t y);

/**
 * @brief Draws the board background image
 * 
 * @param board The board xpm image to be drawn
 * @return Returns 0 upon success and non-zero otherwise
 */
int vg_draw_board(xpm_image_t board);

/**
 * @brief Draws a block of the board starting in x, y, in the "back buffer"
 * 
 * @param img The block xpm image to be drawn
 * @param x The x cooridnate of the top left corner of the image
 * @param y The y cooridnate of the top left corner of the image
 */
void draw_board_block(xpm_image_t img, uint8_t x, uint8_t y);

/**
 * @brief Draws a character from the select font at x, y, scaling it according to user input
 * 
 * @param font The font from which the character should be drawn
 * @param x The x cooridnate of the top left corner of the character
 * @param y The y cooridnate of the top left corner of the character
 * @param scale The scale at which to drawn the character
 * @param pnt A pointer to the start of the character in the font xpm
 */
void vg_draw_character(xpm_image_t font, uint16_t x, uint16_t y, uint8_t scale, uint8_t *pnt);

/**
 * @brief Draws a background to display the player's score with better contrast with the background
 * 
 * @param square The image xpm of the square to be drawn
 * 
 * @return The x position of the drawn xpm
 */
int vg_draw_score_bg(xpm_image_t square);

/**
 * @brief Swaps the "front" and "back" buffers by copying the information from the "back" to the "front" buffer which is the one being drawn in the user's screen
 * 
 */
void swap_buffer();
