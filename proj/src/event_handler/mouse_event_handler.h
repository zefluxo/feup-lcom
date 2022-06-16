#include <stdio.h>
#include "devices/mouse.h"
#include "game/game_state.h"

/**
 * @brief General mouse event handler, calls upon the correct keyboard event handler according to the current game state
 * 
 * @param pp Struct like object with mouse event information
 */
void handle_mouse_event(struct packet pp);

/**
 * @brief Mouse event handler for the main menu game state, handles menu selecting options and clicks, switching to the desired menus
 * 
 * @param pp Struct like object with mouse event information
 */
void handle_mouse_menu_event(struct packet pp);

/**
 * @brief Mouse event handler for the playing game state, handles piece moving by moving the mouse in the left and write direcction, faster drop in the left button and right rotation in the right button
 * 
 * @param pp Struct like object with mouse event information
 */
void handle_mouse_playing_event(struct packet pp);

/**
 * @brief Mouse event handler for the finished game state, handles mouse movement
 * 
 * @param pp Struct like object with mouse event information
 */
void handle_mouse_finished_event(struct packet pp);

/**
 * @brief Mouse event handler for the leaderboard game state, handles mouse movement
 *  
 * @param pp Struct like object with mouse event information
 */
void handle_mouse_leaderboard_event(struct packet pp);
