#pragma once

#include "utils.h"
#include <stdint.h>

/**
 * @brief A struct defining the different types of tetrominos. Letters are used to represent tetrominos that have an identical shape.
 * 
 */
typedef enum {
  CLEAR = 0,
  I,
  J,
  L,
  S,
  O,
  T,
  Z
} tetromino_type;

/**
 * @brief A struct defining the attributes of the tetromino in play
 * 
 */
typedef struct {
  /**
   * @brief The x position of the top leftmost point of the matrix
   * 
   */
  int32_t x;
  /**
   * @brief The y osition of the top leftmost point of the matrix
   * 
   */
  int32_t y;
  /**
   * @brief The type of tetromino
   * 
   */
  tetromino_type type;
  /**
   * @brief The matrix representing the current orientation of the tetromino
   * 
   */
  uint8_t **matrix;
  /**
   * @brief The xpm image that represents the tetromino
   * 
   */
  xpm_image_t image;
} tetromino_t;

/**
 * @brief Verifies if the rotation of the tetromino has placed it within the borders of the play area
 * 
 * @param tetromino A struct like object with information of the current playable tetromino
 */
void check_rotate_inside_border(tetromino_t* tetromino);

/**
 * @brief Attempts to rotate a piece to the left
 * 
 * @param piece A struct like object with information of the current playable tetromino
 */
void rotatePieceLeft(tetromino_t* piece);

/**
 * @brief Attempts to rotate a piece to the right
 * 
 * @param piece A struct like object with information of the current playable tetromino
 */
void rotatePieceRight(tetromino_t* piece);

/**
 * @brief Create a tetromino object with a given type, allocating the necessary memory
 * 
 * @param type The type of tetromino to be created
 * @return tetromino_t* 
 */
tetromino_t* create_tetromino(tetromino_type type);

/**
 * @brief Frees all of the allocated memory for a tetromino
 * 
 * @param tetromino A struct like object with information of the current playable tetromino
 */
void delete_tetromino(tetromino_t * tetromino);
