#include "leaderboard.h"

Array scores;
char name[4];
int name_len = 0;
int lb_entries;

void init_array(Array* a, size_t init_size) {

    a->array = malloc(sizeof(Entry) * init_size);
    a->size = init_size;
    a->used = 0;

}

void insert_array(Array* a, Entry element) {

  if (a->used == a->size) {
      a->size *= 2;
      a->array = realloc(a->array, sizeof(Entry) * a->size);
  }

  a->array[a->used++] = element;

}

void free_array(Array* a) {

    for (size_t i = 0; i < a->used; i++) {
      free(a->array[i].name);
      free(a->array[i].score);
      free(a->array[i].date);
    }

    free(a->array);
    a->array = NULL;
    a->used = 0;
    a->size = 0;
}

//------------------------------------

void get_scores() {

  init_array(&scores, 10);

  FILE* file = fopen("home/lcom/labs/proj/src/game/scores.txt", "r");

  if (file == NULL) {
    printf("file was null :((\n");
    return;
  }

  char line[30];
  fgets(line, 20, file);

  lb_entries = atoi(line);

  while (fgets(line, 30, file)) {
    char name[4];
    strcpy(name, strtok(line, " \n"));

    char score[4];
    sprintf(score, "%d", atoi(strtok(NULL, " \n")));

    char date[11];
    strcpy(date, strtok(NULL, " \n"));

    Entry lb_entry;
    lb_entry.name = strdup(name); lb_entry.score = strdup(score); lb_entry.date = strdup(date);

    insert_array(&scores, lb_entry);
  }

  fclose(file);

}

void draw_scores() {

  Position leaderboard_pos = {100, 200};
  int lines_to_write = (scores.used > 10) ? 10 : scores.used;

  for (int i = 0; i < lines_to_write; i++) {

    draw_string(scores.array[i].name, leaderboard_pos.x, leaderboard_pos.y, 3, true);
    draw_string(scores.array[i].date, leaderboard_pos.x + 260, leaderboard_pos.y, 3, true);
    draw_string(scores.array[i].score, leaderboard_pos.x + 500, leaderboard_pos.y, 3, true);

    leaderboard_pos.y += 30;
    
  }

}

void get_player_entry() {

  Date date = rtc_read_time();
  char date_str[20];

  char day[3];
  char month[3];
  char year[5];

  sprintf(day, "%02d", date.day);
  sprintf(month, "%02d", date.month);
  sprintf(year, "%02d", date.year);

  strcpy(date_str, day);
  strcat(date_str, "/");
  strcat(date_str, month);
  strcat(date_str, "/");
  strcat(date_str, year);

  char score[5];
  sprintf(score, "%d", get_final_score());

  Entry entry;
  entry.name = strdup(name);
  entry.score = strdup(score);
  entry.date = strdup(date_str);

  insert_array(&scores, entry);

}

void draw_player_name() {
    draw_string(name, 360, 280, 4, true);
}

int entry_compare(const void* s1, const void* s2) {

  Entry* e1 = (Entry*) s1;
  Entry* e2 = (Entry*) s2;

  return (atoi(e2->score) - atoi(e1->score));

}

void sort_scores() {
  qsort(scores.array, scores.used, sizeof(Entry), entry_compare);
}

void save_leaderboard() {

  FILE* fp = fopen("home/lcom/labs/proj/src/game/scores.txt", "w");
  if (fp == NULL) {
    fprintf(stderr, "Failed to open scores!\n");
    return;
  }

  char n_entries[10];
  lb_entries++;
  sprintf(n_entries, "%d", lb_entries);
  fprintf(fp, "%s\n", n_entries);

  for (size_t i = 0; i < scores.used; i++) {
    fprintf(fp, "%s %s %s\n", scores.array[i].name, scores.array[i].score, scores.array[i].date);
  }

  fclose(fp);

}

void lb_clean_up() {
  strcpy(name, "");
  name_len = 0;
}
