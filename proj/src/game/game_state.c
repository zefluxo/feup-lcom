#include "game_state.h"

static tetromino_type piece_type[] = {I, J, L, S, O, T, Z};
static int counter = 1;
game_state state = MAIN_MENU;
bool spawned = false;
bool end = false;
bool cleared = false;
int score = 0;
char* score_string = "0";
Position cursor_pos = {400, 300};

void start_game() {
  score = 0;
  spawned = false;
  end = false;
  cleared = false;

  memset(*board, 0, sizeof(board));
  shuffle(piece_type);
  tetromino = create_tetromino(piece_type[0]);
  load_tetromino_image(tetromino);
  place_tetromino();
  draw_game_ui();
  
  draw_board(board);
}

bool check_space() {
  int last_y_idx = 0;
  int iter;  
  if (tetromino->type == I || tetromino->type == O) iter = 4;
  else iter = 3;
  for (int i = 0; i < iter; i++) {
    for (int j = 0; j < iter; j++) {
      if (tetromino->matrix[i][j] != 0) {
        last_y_idx = i;
        if ((board[15 - i - tetromino->y][j + tetromino->x] != 0) && ((i + tetromino->y) >= 0)) {
          return false;
        }
      }
    }
  }
  if (last_y_idx + tetromino->y < 0) {
    end = true;
    return false;
  }
  return true;
}

void place_tetromino() {

  while (!check_space() && !end) {
    tetromino->y--;
  }
  int iter;  
  if (tetromino->type == I || tetromino->type == O) iter = 4;
  else iter = 3;
  for (int i = 0; i < iter; i++) {
    for (int j = 0; j < iter; j++) {
      if ((tetromino->matrix[i][j] != 0) && (i + tetromino->y >= 0)) {
        board[15 - i - tetromino->y][j + tetromino->x] = tetromino->type;
      }
    }
  }
}

bool clear_lines() {
  bool full = true;
  bool clearing = false;
  while (full) {
    for (int i = 0; i < 16; i++) {
      full = true;
      for (int j = 0; j < 10; j++) {
        if (board[i][j] == 0) {
          full = false;
          break;
        }
      }
      if (full) {
        clearing = true;
        score++;
        sprintf(score_string, "%d", score);
        for (int idx = i; idx < 15; idx++) {
          for (int j = 0; j < 10; j++) {
            board[idx][j] = 0;
            board[idx][j] = board[idx+1][j];
          }
        }
        for (int j = 0; j < 10; j++) {
          board[15][j] = 0;
        }
        i--;
      }
    }
  }
  return clearing;
}


void piece_fall() {
  if (end) {
    state = FINISHED;
    delete_tetromino(tetromino);
    return;
  }

  if (!spawned) clear_tetromino();
  bool collision = check_collision(DOWN);

  if (!collision) {
    if (!spawned) tetromino->y += 1;
    spawned = false;
  }
  place_tetromino();

  if (collision) {
    cleared = clear_lines();
    if (cleared) draw_score(score_string);
    delete_tetromino(tetromino);
    tetromino = create_tetromino(piece_type[counter]);
    load_tetromino_image(tetromino);
    counter++;
    spawned = true;
    
    if (counter > 6) {
      counter = 0;
      shuffle(piece_type);
    }
  }
}

void hard_drop(){
  bool collision = check_collision(DOWN);
  while (!collision) {
    clear_tetromino();
    collision = check_collision(DOWN);
    if (!collision) {
      tetromino->y += 1;
    }
    place_tetromino();
  }

  if (collision) {
    cleared = clear_lines();
    if (cleared) draw_score(score_string);
    delete_tetromino(tetromino);
    tetromino = create_tetromino(piece_type[counter]);
    load_tetromino_image(tetromino);
    counter++;
    spawned = true;
    
    if (counter > 6) {
      counter = 0;
      shuffle(piece_type);
    }
  }
}

void clear_tetromino() {
  int iter;  
  if (tetromino->type == I || tetromino->type == O) iter = 4;
  else iter = 3;
  for (int i = 0; i < iter; i++)
    for (int j = 0; j < iter; j++)
      if (tetromino->matrix[i][j] != 0)
        board[15 - i - tetromino->y][j + tetromino->x] = 0;
}

void draw_game_ui() {
  draw_gradient();
  draw_board_bg();
  draw_score(score_string);
}

bool check_collision(collision_dir dir) {
  int y = tetromino->y + 1;
  int left = tetromino->x - 1;
  int right = tetromino->x + 1;
  int iter;  
  if (tetromino->type == I || tetromino->type == O) iter = 4;
  else iter = 3;
  for (int i = 0; i < iter; i++) {
    for (int j = 0; j < iter; j++) {
      switch(dir){
        case DOWN:
          if ((tetromino->matrix[i][j] != 0) && (board[15 - i - y][j + tetromino->x] != 0)) {
            return true;
          }
          if ((tetromino->matrix[i][j] != 0) && (y + (i) > 15)) {
            return true;
          }
          break;
        case LEFT:
          if (((tetromino->matrix[i][j] != 0) && (board[15 - i - tetromino->y][j + left] != 0)) || ((tetromino->matrix[i][j] != 0) && (j + left < 0))) {
            
            return true;
          }
          break;
        case RIGHT:
          if (((tetromino->matrix[i][j] != 0) && (board[15 - i - tetromino->y][j + right] != 0))|| ((tetromino->matrix[i][j] != 0) && (j + right > 9))) {
            return true;
          }
          break;
        case NO_DIR:  
          if ((tetromino->matrix[i][j] != 0) && (board[15 - i - tetromino->y][j + tetromino->x] != 0)) {
            return true;
          }
          break;  
      }
    }
  }
  return false;
}

void move_piece_right() {
  if (spawned) return;
  clear_tetromino();

  bool collision = check_collision(RIGHT);

  if (!collision) {
    tetromino->x += 1;
  }

  place_tetromino();
}

void move_piece_left() {
  if (spawned) return;
  clear_tetromino();

  bool collision = check_collision(LEFT);
  
  if (!collision) {
    tetromino->x -= 1;
  }

  place_tetromino();
}

void piece_rotate(rotate_dir rotation) {
  if (spawned) return;
  clear_tetromino();

  switch(rotation) {
    case R_LEFT: rotatePieceLeft(tetromino); break;
    case R_RIGHT: rotatePieceRight(tetromino); break;
  }
  
  place_tetromino();
}

void update_cursor(uint16_t x_val, uint16_t y_val) {

  uint16_t new_x_pos = cursor_pos.x + x_val;
  uint16_t new_y_pos = cursor_pos.y - y_val;

  if (new_x_pos > 0 && new_x_pos < 800) cursor_pos.x = new_x_pos;
  if (new_y_pos > 0 && new_y_pos < 600) cursor_pos.y = new_y_pos;

}

void move_tetromino(uint16_t x_displacement) {
  tetromino->x += x_displacement;
}

void _main_menu() {
  draw_main_menu();
}

void _leaderboard_menu() {
  draw_leaderboard_menu();
  draw_scores();
}

void _finished_menu() {

  char score_str[5];
  sprintf(score_str, "%d", score);
  draw_finished_menu(score_str);
  
  draw_player_name();

}

void _draw_board() {
  draw_board(board);
}

void _draw_score() {
  char score_str[5];
  sprintf(score_str, "%d", score);
  draw_score(score_str);
}

void cursor_draw() {
  draw_cursor(cursor_pos.x, cursor_pos.y);
}

void cursor_erase() {
  erase_cursor(cursor_pos.x, cursor_pos.y);
}

void check_mouse_clicks() {

  if (cursor_pos.x >= 161 && cursor_pos.x <= 438) {
    
    if (cursor_pos.y >= 304 && cursor_pos.y <= 338){
      state = PLAYING;
      start_game();
    } else if (cursor_pos.y >=402 && cursor_pos.y <= 437) {
      state = LEADERBOARD;
    } else if (cursor_pos.y >= 452 && cursor_pos.y <= 487) {
      state = EXIT;
    }
  }

}

int get_final_score() {
  return score;
}

