#ifndef TETRIS_H
#define TETRIS_H

#define START_X 4
#define START_Y (-4)
#define NUM_FIGURES 7
#define MAX_LEVEL 10
#define SCORE_PER_LEVEL 600
#define DELAY_MS 1100

#include <math.h>
#include <stdlib.h>

#include "../../brick_game.h"

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef enum {
  Initial,
  Spawn,
  Moving,
  Shifting,
  Attaching,
  GameOver
} GameStatus_t;

typedef struct {
  int **field;
  int **figure;
  int figure_size;
  int **next_figure;
  int next_figure_size;
  int x;
  int y;
  int status;
  int score;
  int high_score;
  int level;
  int speed;
  bool pause;
  bool is_playing;
  bool win;
  long long time;
} GameState_t;

void init_game();
int **generate_figure(int *size);
void fill_figure(int number, int **figure);
GameInfo_t updateCurrentState(GameState_t *gs);
void update_field(GameState_t *gs, int **field);
UserAction_t get_user_action(int ch);
void userInput(GameState_t *gs, UserAction_t action);
void finish_game(GameState_t *gs);
void spawn_figure(GameState_t *gs);
void move_figure(GameState_t *gs, UserAction_t action);
void move_left(GameState_t *gs);
void move_right(GameState_t *gs);
void move_down(GameState_t *gs);
void rotate(GameState_t *gs);
void attach_figure(GameState_t *gs);
bool check_top_line(GameState_t *gs);
void process_full_lines(GameState_t *gs);
void shift_lines(GameState_t *gs, int i);
void fill_top_line(GameState_t *gs);
void update_score_and_level(GameState_t *gs, int num_full_lines);

// Utils
GameState_t *get_game_state();
int **create_matrix(int N, int M);
void copy_matrix(int N, int M, int **src_matrix, int **dest_matrix);
void free_matrix(int N, int **matrix);
bool figure_is_attaching(GameState_t *gs);
long long get_time();
bool timer(GameState_t *gs, int delay);
void free_game_info(GameInfo_t *gi);

#endif