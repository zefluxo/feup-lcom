#include "draw_graphics.h"

xpm_image_t tetromino_blue, tetromino_yellow, tetromino_red, tetromino_purple, tetromino_green, tetromino_cyan, tetromino_orange, cursor, empty_cursor, main_menu, font, board, gradient, sidebar, clear, square, blank_menu, font_white;

void _swap_buffer() {
  swap_buffer();
}

int (load_xpms)() {
  xpm_load(tetromino_blue_xpm, XPM_8_8_8, &tetromino_blue);
  xpm_load(tetromino_cyan_xpm, XPM_8_8_8, &tetromino_cyan);
  xpm_load(tetromino_orange_xpm, XPM_8_8_8, &tetromino_orange);
  xpm_load(tetromino_yellow_xpm, XPM_8_8_8, &tetromino_yellow);
  xpm_load(tetromino_purple_xpm, XPM_8_8_8, &tetromino_purple);
  xpm_load(tetromino_red_xpm, XPM_8_8_8, &tetromino_red);
  xpm_load(tetromino_green_xpm, XPM_8_8_8, &tetromino_green);
  xpm_load(font_xpm, XPM_8_8_8, &font);
  xpm_load(cursor_xpm, XPM_8_8_8, &cursor);
  xpm_load(empty_cursor_xpm, XPM_8_8_8, &empty_cursor);
  xpm_load(menu_800x600, XPM_8_8_8, &main_menu);
  xpm_load(gradient_xpm, XPM_8_8_8, &gradient);
  xpm_load(sidebar_xpm, XPM_8_8_8, &sidebar);
  xpm_load(board_xpm, XPM_8_8_8, &board);
  xpm_load(clear_xpm, XPM_8_8_8, &clear);
  xpm_load(square_xpm, XPM_8_8_8, &square);
  xpm_load(blank_menu_xpm, XPM_8_8_8, &blank_menu);
  xpm_load(font_white_xpm, XPM_8_8_8, &font_white);

  return 0;
}

void draw_board_bg() {
  vg_draw_board(board);
}

void draw_main_menu() {
  draw_xpm(main_menu, 0, 0);

  draw_string("SINGLEPLAYER", 200, 312, 3, false);
  draw_string("MULTIPLAYER", 210, 362, 3, false);
  draw_string("LEADERBOARD", 210, 412, 3, false);
  draw_string("EXIT", 270, 462, 3, false);
}

void draw_leaderboard_menu() {
  draw_xpm(blank_menu, 0, 0);

  draw_string("LEADERBOARD", 270, 90, 4, true);
  draw_string("NAME", 100, 150, 3, true);
  draw_string("DATE", 360, 150, 3, true);
  draw_string("SCORE", 600, 150, 3, true);
}

void draw_gradient() {
  draw_xpm(gradient, 0, 0);
}

void draw_score(char *score) {
  uint16_t offset = vg_draw_score_bg(square);

  uint16_t score_x = offset + 100 - (18 * strlen(score) + 10) ;
  uint16_t score_y = 38;
  
  uint16_t text_x = offset + 10;
  uint16_t text_y = 12;

  draw_string("SCORE", text_x, text_y, 3, false);
  draw_string(score, score_x, score_y, 3, false);
}

void load_tetromino_image(tetromino_t *tetromino) {
  switch(tetromino->type) {
    case CLEAR:
      break;
    case J:
      tetromino->image = tetromino_blue;
      break;
    case I:
      tetromino->image = tetromino_cyan;
      break;
    case L:
      tetromino->image = tetromino_orange;
      break;
    case S:
      tetromino->image = tetromino_green;
      break;
    case O:
      tetromino->image = tetromino_yellow;
      break;
    case T:
      tetromino->image = tetromino_purple;
      break;
    case Z:
      tetromino->image = tetromino_red;
      break;
  }
} 

void draw_board(tetromino_type board[16][10]) {
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 10; j++) {
      switch(board[i][j]) {
        case CLEAR:
          draw_board_block(clear, j, i);
          break;
        case J:
          draw_board_block(tetromino_blue, j, i);
          break;
        case I:
          draw_board_block(tetromino_cyan, j, i);
          break;
        case L:
          draw_board_block(tetromino_orange, j, i);
          break;
        case S:
          draw_board_block(tetromino_green, j, i);
          break;
        case O:
          draw_board_block(tetromino_yellow, j, i);
          break;
        case T:
          draw_board_block(tetromino_purple, j, i);
          break;
        case Z:
          draw_board_block(tetromino_red, j, i);
          break;
      }        
    }
  }
}

void draw_string(const char *string, uint16_t x, uint16_t y, uint8_t scale, bool white) {
  for (unsigned int i = 0; i < strlen(string); i++) {
    if (string[i] != ' ' && string[i] != '/') {
      draw_character(string[i], x + (scale * 6 * i) , y, scale, white);
    } else {
      i++;
      draw_character(string[i], x + (scale * 6 * i) , y, scale, white);
    }
  }
}

void draw_character(const char character, uint16_t x, uint16_t y, uint8_t scale, bool white) {
  uint8_t *pnt = NULL;
  uint8_t font_bpp = (font.size / (font.height * font.width));
  unsigned char *init_pnt;

  if (white) {
    init_pnt = font_white.bytes;
  } else {
    init_pnt = font.bytes;
  }
  
  if (!is_alpha(character)) {
    int num = character - '0';
    pnt = init_pnt + (6 * num) * font_bpp;
  } else {
    int num = (int) character - 65;
    if (num < 0 || num > 25) return;

    if (num >=0 && num <= 14) {
      pnt = init_pnt + (6 * (num + 1)) * font_bpp + (font.width * 7) * font_bpp;
    } else if (num >= 15 && num <=25) {
      pnt = init_pnt + (6 * (num - 15)) * font_bpp + (font.width * 14) * font_bpp;
    }
  }

  if (white) {
    vg_draw_character(font_white, x, y, scale, pnt);
  } else {
    vg_draw_character(font, x, y, scale, pnt);
  }
}

void draw_cursor(uint16_t x, uint16_t y) {
  draw_xpm(cursor, x, y);
}

void erase_cursor(uint16_t x, uint16_t y) {
  draw_xpm(empty_cursor, x, y);
}

void draw_finished_menu(const char* score) {
  draw_xpm(blank_menu, 0, 0);

  draw_string("GAME OVER", 294, 90, 4, true);

  draw_string("YOUR SCORE", 310, 150, 3, true);
  
  draw_string(score, 382, 180, 3, true);

  draw_string("ENTER YOUR NAME", 260, 250, 3, true);

  draw_string("PRESS ESC TO CONTINUE", 210, 500, 3, true);

}
