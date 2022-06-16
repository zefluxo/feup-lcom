#include "kbd_event_handler.h"

void handle_kbd_event(uint8_t scan_code[2]) {
  
  switch (state) {
    case MAIN_MENU: break;
    case PLAYING: handle_kbd_playing_event(scan_code); break;
    case FINISHED: handle_kbd_finished_event(scan_code); break;
    case LEADERBOARD: handle_kbd_leaderboard_event(scan_code); break;
    case EXIT: break;
  }

}

void handle_kbd_playing_event(uint8_t scan_code[2]) {

  if (scan_code[0] == TWO_BYTE_SC) {

    switch (scan_code[1]) {
      case LEFT_ARROW: move_piece_left(); break;
      case RIGHT_ARROW: move_piece_right(); break;
      case DOWN_ARROW: piece_fall(); break;
      default: break;
    }

  } else {

    switch (scan_code[0]) {
      case Z_KEY | IS_BREAK: piece_rotate(R_LEFT); break;
      case X_KEY | IS_BREAK: piece_rotate(R_RIGHT); break;
      default: break;
    }

  }

}

void handle_kbd_finished_event(uint8_t scan_code[2]) {
  switch (scan_code[0]) {
    case ESC_BREAK: {

      if (name_len < 3) { break; }

      get_player_entry();
      sort_scores();
      save_leaderboard();

      lb_clean_up();
      state = MAIN_MENU;

      break;
    }

    default: {
      if (keys[scan_code[0]] != 0 && name_len < 3) {

        // black magic :)
        char* ch = strdup(&keys[scan_code[0]]);
        *(ch + 1) = '\0';

        strcat(name, ch); 
        free(ch);
        name_len++;

      }
      break;
    }
  }
}

void handle_kbd_leaderboard_event(uint8_t scan_code[2]) {
  switch (scan_code[0]) {
    case ESC_BREAK: {
      state = MAIN_MENU;
      break;
    }
  }
}
