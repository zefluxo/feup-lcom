#include "mouse_event_handler.h"

void handle_mouse_event(struct packet pp) {
  
  switch(state) {
    case MAIN_MENU: handle_mouse_menu_event(pp); break;
    case PLAYING: handle_mouse_playing_event(pp); break;
    case FINISHED: handle_mouse_finished_event(pp); break;
    case LEADERBOARD: handle_mouse_leaderboard_event(pp); break;
    case EXIT: break;
  }

}

void handle_mouse_playing_event(struct packet pp) {

  if (pp.lb && (pp.delta_x == 0)) piece_fall();
  if (pp.rb && (pp.delta_x == 0)) piece_rotate(R_RIGHT);

  if (pp.delta_x < 0) {
    move_piece_left();
  } else if (pp.delta_x > 0) {
    move_piece_right();
  }
}

void handle_mouse_menu_event(struct packet pp) {

  update_cursor(pp.delta_x, pp.delta_y);
  if (pp.lb) check_mouse_clicks();

}

void handle_mouse_finished_event(struct packet pp) {
  update_cursor(pp.delta_x, pp.delta_y);
}

void handle_mouse_leaderboard_event(struct packet pp) {
  update_cursor(pp.delta_x, pp.delta_y);
}
