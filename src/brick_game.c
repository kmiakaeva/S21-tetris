#include "brick_game.h"

int main() {
  init_ncurses();
  init_colors();
  init_game();
  game_loop();

  endwin();

  return 0;
}

void game_loop() {
  bool is_playing = true;

  while (is_playing) {
    GameState_t *gs = get_game_state();
    GameInfo_t gi = updateCurrentState(gs);

    int ch = getch();

    render(gs->status, gs->win, gi);
    free_game_info(&gi);

    if (gs->status == GameOver || gs->win) {
      while (ch != 'r' && ch != 'q') ch = getch();
      init_game();
    }

    timeout(10);

    userInput(gs, get_user_action(ch));
    is_playing = gs->is_playing;
  }
}