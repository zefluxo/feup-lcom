#pragma once

#include <lcom/timer.h>

#include "timer.h"
#include "keyboard.h"
#include "mouse.h"

#include "game/game_state.h"

#include "../event_handler/kbd_event_handler.h"
#include "../event_handler/mouse_event_handler.h"
#include "../event_handler/timer_event_handler.h"

/* Tetrominos falling speed */
#define SLOW 40
#define NORMAL 30
#define FAST 20

/**
 * @brief Function called at program start, enables interrupts, intializes videocard, loads xpms and initializes other important features
 * 
 */
int (init)();

/**
 * @brief The main program execution loop, responsible for calling all of the needed functions to run the game and menus
 * 
 */
int (main_loop)();

/**
 * @brief Function executed on program end, unsubscribes interrupts and overall resets MINIX to its' default mode
 * 
 */
int (leave)();
