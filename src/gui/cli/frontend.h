#ifndef FRONTEND_H
#define FRONTEND_H

#define GAME_FIELD_N (FIELD_N + 2)
#define GAME_FIELD_M (FIELD_M * 3 + 2)
#define START_MENU_N 8
#define START_MENU_M 24
#define PAUSE_MENU_N 5
#define PAUSE_MENU_M 24
#define FINISH_GAME_N 10
#define FINISH_GAME_M 24
#define GAME_INFO_M 25
#define CONTROLS_M 24

#define TOP_MARGIN 0
#define LEFT_MARGIN 0

#include <ncurses.h>

#include "../../brick_game.h"

void init_ncurses();
void init_colors();
void render(int status, bool win, GameInfo_t gi);
WINDOW *print_controls();
WINDOW *print_game_field(GameInfo_t gi);
void print_start_menu();
void print_pause_menu();
void print_win(GameInfo_t gi);
void print_game_over(GameInfo_t gi);
WINDOW *print_game_info(GameInfo_t gi);
void print_next_figure(WINDOW *info_window, GameInfo_t gi);

#endif