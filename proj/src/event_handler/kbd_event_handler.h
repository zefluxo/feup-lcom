#include <stdio.h>
#include "../devices/keyboard.h"
#include "../game/game_state.h"

/**
 * @brief General keyboard event handler, calls upon the correct keyboard event handler according to the current game state
 * 
 * @param scan_code The scan code of the pressed key
 */
void handle_kbd_event(uint8_t scan_code[2]);

/**
 * @brief Keyboard event handler for the playing game state, handles rotations in the Z and X keys and piece movement in the arrow keys
 * 
 * @param scan_code The scan code of the pressed key
 */
void handle_kbd_playing_event(uint8_t scan_code[2]);

/**
 * @brief Keyboard event handler for the finished game state, handles name writing and exiting of this menu
 * 
 * @param scan_code The scan code of the pressed key
 */
void handle_kbd_finished_event(uint8_t scan_code[2]);

/**
 * @brief Keyboard event handler for the leaderboard game state, handles exiting of this menu
 * 
 * @param scan_code The scan code of the pressed key
 */
void handle_kbd_leaderboard_event(uint8_t scan_code[2]);
