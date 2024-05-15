#include "unit_test.h"

START_TEST(init_1) {
  init_game();
  GameState_t *gs = get_game_state();
  GameInfo_t gi = updateCurrentState(gs);

  ck_assert_int_eq(gs->score, 0);

  finish_game(gs);
  free_game_info(&gi);
}
END_TEST

START_TEST(init_2) {
  init_game();
  GameState_t *gs = get_game_state();
  GameInfo_t gi = updateCurrentState(gs);

  ck_assert_int_eq(gs->level, 1);

  finish_game(gs);
  free_game_info(&gi);
}
END_TEST

START_TEST(init_3) {
  init_game();
  GameState_t *gs = get_game_state();
  GameInfo_t gi = updateCurrentState(gs);

  ck_assert_int_eq(gs->pause, false);

  finish_game(gs);
  free_game_info(&gi);
}
END_TEST

START_TEST(init_4) {
  init_game();
  GameState_t *gs = get_game_state();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, get_user_action(KEY_Q));
  ck_assert_int_eq(gs->is_playing, false);

  free_game_info(&gi);
}
END_TEST

START_TEST(start_1) {
  init_game();
  GameState_t *gs = get_game_state();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, get_user_action(KEY_R));
  ck_assert_int_eq(gs->status, Spawn);

  finish_game(gs);
  free_game_info(&gi);
}
END_TEST

START_TEST(spawn_1) {
  init_game();
  GameState_t *gs = get_game_state();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, get_user_action(KEY_R));
  userInput(gs, get_user_action(KEY_Q));
  ck_assert_int_eq(gs->is_playing, false);

  free_game_info(&gi);
}
END_TEST

START_TEST(spawn_2) {
  init_game();
  GameState_t *gs = get_game_state();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, get_user_action(KEY_R));
  userInput(gs, get_user_action(ERR));
  ck_assert_int_eq(gs->status, Moving);

  finish_game(gs);
  free_game_info(&gi);
}
END_TEST

START_TEST(moving_left) {
  init_game();
  GameState_t *gs = get_game_state();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, get_user_action(KEY_R));
  userInput(gs, get_user_action(ERR));
  userInput(gs, get_user_action(KEY_LEFT));
  ck_assert_int_eq(gs->pause, false);
  ck_assert_int_eq(gs->status, Moving);

  finish_game(gs);
  free_game_info(&gi);
}
END_TEST

START_TEST(moving_right) {
  init_game();
  GameState_t *gs = get_game_state();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, get_user_action(KEY_R));
  userInput(gs, get_user_action(ERR));
  userInput(gs, get_user_action(KEY_RIGHT));
  ck_assert_int_eq(gs->pause, false);
  ck_assert_int_eq(gs->status, Moving);

  finish_game(gs);
  free_game_info(&gi);
}
END_TEST

START_TEST(moving_down) {
  init_game();
  GameState_t *gs = get_game_state();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, get_user_action(KEY_R));
  userInput(gs, get_user_action(ERR));
  userInput(gs, get_user_action(KEY_DOWN));
  ck_assert_int_eq(gs->pause, false);
  ck_assert_int_eq(gs->status, Moving);

  finish_game(gs);
  free_game_info(&gi);
}
END_TEST

START_TEST(moving_action) {
  init_game();
  GameState_t *gs = get_game_state();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, get_user_action(KEY_R));
  userInput(gs, get_user_action(ERR));
  userInput(gs, get_user_action(KEY_Z));
  ck_assert_int_eq(gs->pause, false);
  ck_assert_int_eq(gs->status, Moving);

  finish_game(gs);
  free_game_info(&gi);
}
END_TEST

START_TEST(moving_up) {
  init_game();
  GameState_t *gs = get_game_state();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, get_user_action(KEY_R));
  userInput(gs, get_user_action(ERR));
  userInput(gs, get_user_action(KEY_UP));
  ck_assert_int_eq(gs->pause, false);
  ck_assert_int_eq(gs->status, Moving);

  finish_game(gs);
  free_game_info(&gi);
}
END_TEST

START_TEST(moving_pause) {
  init_game();
  GameState_t *gs = get_game_state();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, get_user_action(KEY_R));
  userInput(gs, get_user_action(ERR));
  userInput(gs, get_user_action(KEY_P));
  ck_assert_int_eq(gs->pause, true);
  ck_assert_int_eq(gs->status, Moving);

  finish_game(gs);
  free_game_info(&gi);
}
END_TEST

START_TEST(moving_terminate) {
  init_game();
  GameState_t *gs = get_game_state();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, get_user_action(KEY_R));
  userInput(gs, get_user_action(ERR));
  userInput(gs, get_user_action(KEY_Q));
  ck_assert_int_eq(gs->is_playing, false);
  ck_assert_int_eq(gs->status, Moving);

  free_game_info(&gi);
}
END_TEST

START_TEST(attaching_1) {
  init_game();
  GameState_t *gs = get_game_state();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, get_user_action(KEY_R));
  userInput(gs, get_user_action(ERR));

  while (gs->status != Attaching) {
    userInput(gs, get_user_action(KEY_DOWN));
  }
  userInput(gs, get_user_action(ERR));

  ck_assert_int_eq(gs->status, Spawn);

  finish_game(gs);
  free_game_info(&gi);
}
END_TEST

START_TEST(gameover_1) {
  init_game();
  GameState_t *gs = get_game_state();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, get_user_action(KEY_R));
  userInput(gs, get_user_action(ERR));

  while (gs->status != GameOver) {
    userInput(gs, get_user_action(KEY_DOWN));
  }
  userInput(gs, get_user_action(ERR));

  ck_assert_int_eq(gs->is_playing, true);
  ck_assert_int_eq(gs->status, GameOver);

  free_game_info(&gi);
}
END_TEST

Suite *tetris_suite() {
  Suite *s = suite_create("tetris_suite");
  TCase *tc = tcase_create("tetris_tc");

  tcase_add_test(tc, init_1);
  tcase_add_test(tc, init_2);
  tcase_add_test(tc, init_3);
  tcase_add_test(tc, init_4);
  tcase_add_test(tc, start_1);
  tcase_add_test(tc, spawn_1);
  tcase_add_test(tc, spawn_2);
  tcase_add_test(tc, moving_left);
  tcase_add_test(tc, moving_right);
  tcase_add_test(tc, moving_down);
  tcase_add_test(tc, moving_action);
  tcase_add_test(tc, moving_up);
  tcase_add_test(tc, moving_pause);
  tcase_add_test(tc, moving_terminate);
  tcase_add_test(tc, attaching_1);
  tcase_add_test(tc, gameover_1);

  suite_add_tcase(s, tc);

  return s;
}

int main() {
  Suite *s = tetris_suite();
  SRunner *sr = srunner_create(s);
  int tf = 0;

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  tf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return tf > 0;
}