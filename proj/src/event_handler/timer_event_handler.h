#include <stdio.h>
#include "devices/timer.h"
#include <lcom/timer.h>
#include "devices/int_manager.h"
#include "game/game_state.h"

/**
 * @brief General keyboard event handler, calls upon the correct keyboard event handler according to the current game state
 * 
 */
void handle_timer_event();

/**
 * @brief Timer event handler for the main menu game state, handles screen updates
 * 
 */
void handle_timer_menu_event();

/**
 * @brief Timer event handler for the main menu game state, handles screen updates
 * 
 */
void handle_timer_playing_event();

/**
 * @brief Timer event handler for the playing game state, handles screen updates
 * 
 */
void handle_timer_finished_event();

/**
 * @brief Timer event handler for the leaderboard game state, handles screen updates
 * 
 */
void handle_timer_leaderboard_event();
