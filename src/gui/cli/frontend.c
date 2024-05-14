#include "frontend.h"

void init_ncurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, 1);
  nodelay(stdscr, 1);
  scrollok(stdscr, 1);
  curs_set(0);
  mouseinterval(1);
}

void init_colors() {
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(4, COLOR_RED, COLOR_BLACK);
  init_pair(5, COLOR_CYAN, COLOR_CYAN);
  init_pair(6, COLOR_GREEN, COLOR_BLACK);
}

void render(int status, bool win, GameInfo_t gi) {
  refresh();

  WINDOW *controls_window = print_controls();
  wrefresh(controls_window);

  WINDOW *game_window = NULL;
  if (!gi.pause) {
    game_window = print_game_field(gi);
    wrefresh(game_window);
  }

  if (status == Initial)
    print_start_menu();
  else if (gi.pause)
    print_pause_menu();
  else if (win)
    print_win(gi);
  else if (status == GameOver)
    print_game_over(gi);

  WINDOW *info_window = print_game_info(gi);
  wrefresh(info_window);

  if (game_window != NULL) delwin(game_window);

  delwin(info_window);
  delwin(controls_window);
}

void print_start_menu() {
  WINDOW *start_menu_window =
      newwin(START_MENU_N, START_MENU_M, (GAME_FIELD_N - START_MENU_N) / 2,
             GAME_FIELD_M - (GAME_FIELD_M - START_MENU_M) / 2 + 1);
  box(start_menu_window, 0, 0);

  // Borders
  mvwhline(start_menu_window, 1, 2, ACS_HLINE, START_MENU_M - 4);
  mvwhline(start_menu_window, START_MENU_N - 2, 2, ACS_HLINE, START_MENU_M - 4);
  mvwvline(start_menu_window, 2, 1, ACS_VLINE, START_MENU_N - 4);
  mvwvline(start_menu_window, 2, START_MENU_M - 2, ACS_VLINE, START_MENU_N - 4);

  // Text
  int text_width = 20;
  int text_height = 3;

  wattron(start_menu_window, COLOR_PAIR(1));
  mvwprintw(start_menu_window, (START_MENU_N - text_height) / 2,
            (START_MENU_M - text_width) / 2 + 1, "Welcome to Tetris");
  mvwprintw(start_menu_window, (START_MENU_N - text_height) / 2 + 1,
            (START_MENU_M - text_width) / 2 + 2, "from MC Kris! :)");
  wattroff(start_menu_window, COLOR_PAIR(1));

  wattron(start_menu_window, COLOR_PAIR(2));
  mvwprintw(start_menu_window, (START_MENU_N - text_height) / 2 + 3,
            (START_MENU_M - text_width) / 2 + 1, "Press 'r' to start");
  wattroff(start_menu_window, COLOR_PAIR(2));

  wrefresh(start_menu_window);
  delwin(start_menu_window);
}

void print_pause_menu() {
  WINDOW *pause_menu_window =
      newwin(PAUSE_MENU_N, PAUSE_MENU_M, (GAME_FIELD_N - PAUSE_MENU_N) / 2,
             CONTROLS_M + (GAME_FIELD_M - PAUSE_MENU_M) / 2 + 1);
  box(pause_menu_window, 0, 0);
  wbkgd(pause_menu_window, COLOR_PAIR(3));

  // Borders
  mvwhline(pause_menu_window, 1, 2, ACS_HLINE, PAUSE_MENU_M - 4);
  mvwhline(pause_menu_window, PAUSE_MENU_N - 2, 2, ACS_HLINE, PAUSE_MENU_M - 4);
  mvwvline(pause_menu_window, 2, 2, ACS_VLINE, PAUSE_MENU_N - 4);
  mvwvline(pause_menu_window, 2, PAUSE_MENU_M - 3, ACS_VLINE, PAUSE_MENU_N - 4);

  // Text
  int text_width = 6;
  int text_height = 1;

  mvwprintw(pause_menu_window, (PAUSE_MENU_N - text_height) / 2,
            (PAUSE_MENU_M - text_width) / 2, "Paused");

  wrefresh(pause_menu_window);
  delwin(pause_menu_window);
}

void print_win(GameInfo_t gi) {
  WINDOW *win_window =
      newwin(FINISH_GAME_N, FINISH_GAME_M, (GAME_FIELD_N - FINISH_GAME_N) / 2,
             CONTROLS_M + (GAME_FIELD_M - FINISH_GAME_M) / 2 + 1);
  box(win_window, 0, 0);
  wbkgd(win_window, COLOR_PAIR(6));

  // Borders
  mvwhline(win_window, 1, 1, ACS_HLINE, FINISH_GAME_M - 2);
  mvwhline(win_window, FINISH_GAME_N - 2, 1, ACS_HLINE, FINISH_GAME_M - 2);
  mvwvline(win_window, 1, 1, ACS_VLINE, FINISH_GAME_N - 2);
  mvwvline(win_window, 1, FINISH_GAME_M - 2, ACS_VLINE, FINISH_GAME_N - 2);

  // Text
  int text_width = 11;
  int text_height = 2;

  mvwprintw(win_window, (FINISH_GAME_N - text_height) / 2,
            (FINISH_GAME_M - text_width) / 2, "You win! :)");
  mvwprintw(win_window, (FINISH_GAME_N - text_height) / 2 + 2,
            (FINISH_GAME_M - text_width) / 2, "Score  %d", gi.score);

  wrefresh(win_window);
  delwin(win_window);
}

void print_game_over(GameInfo_t gi) {
  WINDOW *game_over_window =
      newwin(FINISH_GAME_N, FINISH_GAME_M, (GAME_FIELD_N - FINISH_GAME_N) / 2,
             CONTROLS_M + (GAME_FIELD_M - FINISH_GAME_M) / 2 + 1);
  box(game_over_window, 0, 0);
  wbkgd(game_over_window, COLOR_PAIR(4));

  // Borders
  mvwhline(game_over_window, 1, 1, ACS_HLINE, FINISH_GAME_M - 2);
  mvwhline(game_over_window, FINISH_GAME_N - 2, 1, ACS_HLINE,
           FINISH_GAME_M - 2);
  mvwvline(game_over_window, 1, 1, ACS_VLINE, FINISH_GAME_N - 2);
  mvwvline(game_over_window, 1, FINISH_GAME_M - 2, ACS_VLINE,
           FINISH_GAME_N - 2);

  // Text
  int text_width = 12;
  int text_height = 4;

  mvwprintw(game_over_window, (FINISH_GAME_N - text_height) / 2,
            (FINISH_GAME_M - text_width) / 2, "Game over :(");
  mvwprintw(game_over_window, (FINISH_GAME_N - text_height) / 2 + 2,
            (FINISH_GAME_M - text_width) / 2, "Score  %d", gi.score);
  mvwprintw(game_over_window, (FINISH_GAME_N - text_height) / 2 + 3,
            (FINISH_GAME_M - text_width) / 2, "Level  %d", gi.level);

  wrefresh(game_over_window);
  delwin(game_over_window);
}

WINDOW *print_controls() {
  WINDOW *controls_window =
      newwin(GAME_FIELD_N, CONTROLS_M, TOP_MARGIN, LEFT_MARGIN);
  box(controls_window, 0, 0);

  mvwprintw(controls_window, 0, (CONTROLS_M - 8) / 2, "Controls");

  mvwprintw(controls_window, 2, 2, "Start    r");
  mvwprintw(controls_window, 4, 2, "Pause    p");
  mvwprintw(controls_window, 6, 2, "Rotate   z, up arrow");
  mvwprintw(controls_window, 8, 2, "Left     left arrow");
  mvwprintw(controls_window, 10, 2, "Right    right arrow");
  mvwprintw(controls_window, 12, 2, "Down     down arrow");
  mvwprintw(controls_window, 14, 2, "Quit     q");

  return controls_window;
}

WINDOW *print_game_field(GameInfo_t gi) {
  WINDOW *game_window =
      newwin(GAME_FIELD_N, GAME_FIELD_M, TOP_MARGIN, CONTROLS_M + 1);

  box(game_window, 0, 0);
  keypad(game_window, 1);
  nodelay(game_window, 1);

  mvwprintw(game_window, 0, (GAME_FIELD_M - 6) / 2, "Tetris");

  for (int i = 0; i < FIELD_N; i++) {
    for (int j = 0; j < FIELD_M; j++) {
      if (gi.field[i][j] == 1) {
        wattron(game_window, COLOR_PAIR(5));
        mvwprintw(game_window, i + 1, 3 * j + 1, "   ");
        wattroff(game_window, COLOR_PAIR(5));
      } else {
        wattron(game_window, COLOR_PAIR(1));
        mvwprintw(game_window, i + 1, 3 * j + 1, "  .");
        wattroff(game_window, COLOR_PAIR(1));
      }
    }
  }

  return game_window;
}

WINDOW *print_game_info(GameInfo_t gi) {
  WINDOW *info_window = newwin(GAME_FIELD_N, GAME_INFO_M, TOP_MARGIN,
                               CONTROLS_M + GAME_FIELD_M + 1);
  box(info_window, 0, 0);

  mvwprintw(info_window, 0, (GAME_INFO_M - 9) / 2, "Game_Info");

  print_next_figure(info_window, gi);

  mvwprintw(info_window, 8, 2, "High score  %d", gi.high_score);
  mvwprintw(info_window, 11, 2, "Score       %d", gi.score);
  mvwprintw(info_window, 14, 2, "Level       %d", gi.level);
  mvwprintw(info_window, 17, 2, "Speed       %d", gi.speed);

  return info_window;
}

void print_next_figure(WINDOW *info_window, GameInfo_t gi) {
  mvwprintw(info_window, 2, 2, "Next");

  for (int i = 0; i < gi.next_size; i++) {
    for (int j = 0; j < gi.next_size; j++) {
      if (gi.next[i][j] == 1) {
        wattron(info_window, COLOR_PAIR(5));
        mvwprintw(info_window, i + 4, j * 3 + 4, "   ");
        wattroff(info_window, COLOR_PAIR(5));
      }
    }
  }
}