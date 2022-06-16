#pragma once

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "devices/keyboard.h"

/**
 * @brief Reverses the columns of a matrix
 * 
 * @param arr The array to be reversed
 * @param R The number of rows
 * @param C The number of columns
 */
void reverseColumns(uint8_t **arr, unsigned R, unsigned C);

/**
 * @brief Reverses the rows of a matrix
 * 
 * @param arr The array to be reversed
 * @param R The number of rows
 * @param C The number of columns
 */
void reverseRows(uint8_t **arr, unsigned R, unsigned C);

/**
 * @brief Transposes a matrix
 * 
 * @param arr The matrix to be transposed
 * @param R The number of rows
 * @param C The number of columns
 */
void transpose(uint8_t **arr, unsigned R, unsigned C);

/**
 * @brief Prints a martix (for debug purposes)
 * 
 * @param arr The matrix to be printed
 * @param R The number of rows
 * @param C The number of columns
 */
void printMatrix(uint8_t **arr, unsigned R, unsigned C);

/**
 * @brief Rotates a matrix to the left, calling the correct functions for this purpose
 * 
 * @param arr The matrix to be rotated
 * @param R The number of rows
 * @param C The number of columns
 */
void rotateLeft(uint8_t **arr, unsigned R, unsigned C);

/**
 * @brief Rotates a matrix to the right, calling the correct functions for this purpose
 * 
 * @param arr The matrix to be rotated
 * @param R The number of rows
 * @param C The number of columns
 */
void rotateRight(uint8_t **arr, unsigned R, unsigned C);

/**
 * @brief Checks if a character is alphanumeric
 * 
 * @param character The character to be evaluated
 *
 * @return True if is an alpha numeric character 
 */
bool is_alpha(char character);

/**
 * @brief Get the keys object
 * 
 */
void get_keys();
