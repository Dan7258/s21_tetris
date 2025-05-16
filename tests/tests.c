#include "tests.h"

START_TEST(create_test) {
  matrix_t result;
  int rows = 3;
  int columns = 4;

  create_matrix(rows, columns, &result);

  ck_assert_int_eq(result.rows, rows);
  ck_assert_int_eq(result.columns, columns);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_int_eq(result.matrix[i][j], 0);
    }
  }

  for (int i = 0; i < rows; i++) {
    free(result.matrix[i]);
  }
  free(result.matrix);

  create_matrix(3, 4, NULL);
  ck_assert(1);
}
END_TEST

START_TEST(remove_test) {
  matrix_t M;
  int rows = 3;
  int columns = 3;

  create_matrix(rows, columns, &M);
  remove_matrix(&M);

  ck_assert_ptr_null(M.matrix);
  ck_assert_int_eq(M.rows, 0);
  ck_assert_int_eq(M.columns, 0);
}
END_TEST

START_TEST(turn_left_test) {
  matrix_t M;
  int rows = 3;
  int columns = 3;

  create_matrix(rows, columns, &M);

  int counter = 1;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      M.matrix[i][j] = counter++;
    }
  }

  turn_left_matrix(&M);

  int expected[3][3] = {{3, 6, 9}, {2, 5, 8}, {1, 4, 7}};

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_int_eq(M.matrix[i][j], expected[i][j]);
    }
  }

  remove_matrix(&M);
}
END_TEST

START_TEST(turn_right_test) {
  matrix_t M;
  int rows = 3;
  int columns = 3;

  create_matrix(rows, columns, &M);

  int counter = 1;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      M.matrix[i][j] = counter++;
    }
  }

  turn_right_matrix(&M);

  int expected[3][3] = {{7, 4, 1}, {8, 5, 2}, {9, 6, 3}};

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_int_eq(M.matrix[i][j], expected[i][j]);
    }
  }

  remove_matrix(&M);
}
END_TEST

START_TEST(test_create_figure_O) {
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  create_figure(O, &figure);

  ck_assert_int_eq(figure.matrix->rows, 2);
  ck_assert_int_eq(figure.matrix->columns, 2);

  ck_assert_int_eq(figure.matrix->matrix[0][0], 1);
  ck_assert_int_eq(figure.matrix->matrix[0][1], 1);
  ck_assert_int_eq(figure.matrix->matrix[1][0], 1);
  ck_assert_int_eq(figure.matrix->matrix[1][1], 1);

  ck_assert_int_eq(figure.x, 4);
  ck_assert_int_eq(figure.y, -2);

  remove_figure(&figure);
}
END_TEST

START_TEST(test_create_figure_I) {
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  create_figure(I, &figure);

  ck_assert_int_eq(figure.matrix->rows, 4);
  ck_assert_int_eq(figure.matrix->columns, 4);

  ck_assert_int_eq(figure.matrix->matrix[2][0], 1);
  ck_assert_int_eq(figure.matrix->matrix[2][1], 1);
  ck_assert_int_eq(figure.matrix->matrix[2][2], 1);
  ck_assert_int_eq(figure.matrix->matrix[2][3], 1);

  ck_assert_int_eq(figure.x, 3);
  ck_assert_int_eq(figure.y, -3);

  remove_figure(&figure);
}
END_TEST

START_TEST(test_create_figure_S) {
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  create_figure(S, &figure);

  ck_assert_int_eq(figure.matrix->rows, 3);
  ck_assert_int_eq(figure.matrix->columns, 3);

  ck_assert_int_eq(figure.matrix->matrix[0][0], 1);
  ck_assert_int_eq(figure.matrix->matrix[1][0], 1);
  ck_assert_int_eq(figure.matrix->matrix[1][1], 1);
  ck_assert_int_eq(figure.matrix->matrix[2][1], 1);

  ck_assert_int_eq(figure.x, 4);
  ck_assert_int_eq(figure.y, -3);

  remove_figure(&figure);
}
END_TEST

START_TEST(test_create_figure_Z) {
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  create_figure(Z, &figure);

  ck_assert_int_eq(figure.matrix->rows, 3);
  ck_assert_int_eq(figure.matrix->columns, 3);

  ck_assert_int_eq(figure.matrix->matrix[0][1], 1);
  ck_assert_int_eq(figure.matrix->matrix[1][1], 1);
  ck_assert_int_eq(figure.matrix->matrix[1][0], 1);
  ck_assert_int_eq(figure.matrix->matrix[2][0], 1);

  ck_assert_int_eq(figure.x, 4);
  ck_assert_int_eq(figure.y, -3);

  remove_figure(&figure);
}
END_TEST

START_TEST(test_create_figure_L) {
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  create_figure(L, &figure);

  ck_assert_int_eq(figure.matrix->rows, 3);
  ck_assert_int_eq(figure.matrix->columns, 3);

  ck_assert_int_eq(figure.matrix->matrix[0][1], 1);
  ck_assert_int_eq(figure.matrix->matrix[1][1], 1);
  ck_assert_int_eq(figure.matrix->matrix[2][1], 1);
  ck_assert_int_eq(figure.matrix->matrix[2][2], 1);

  ck_assert_int_eq(figure.x, 3);
  ck_assert_int_eq(figure.y, -3);

  remove_figure(&figure);
}
END_TEST

START_TEST(test_create_figure_J) {
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  create_figure(J, &figure);

  ck_assert_int_eq(figure.matrix->rows, 3);
  ck_assert_int_eq(figure.matrix->columns, 3);

  ck_assert_int_eq(figure.matrix->matrix[0][2], 1);
  ck_assert_int_eq(figure.matrix->matrix[1][2], 1);
  ck_assert_int_eq(figure.matrix->matrix[2][2], 1);
  ck_assert_int_eq(figure.matrix->matrix[2][1], 1);

  ck_assert_int_eq(figure.x, 3);
  ck_assert_int_eq(figure.y, -3);

  remove_figure(&figure);
}
END_TEST

START_TEST(test_create_figure_T) {
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  create_figure(T, &figure);

  ck_assert_int_eq(figure.matrix->rows, 3);
  ck_assert_int_eq(figure.matrix->columns, 3);

  ck_assert_int_eq(figure.matrix->matrix[1][0], 1);
  ck_assert_int_eq(figure.matrix->matrix[1][1], 1);
  ck_assert_int_eq(figure.matrix->matrix[1][2], 1);
  ck_assert_int_eq(figure.matrix->matrix[2][1], 1);

  ck_assert_int_eq(figure.x, 4);
  ck_assert_int_eq(figure.y, -3);

  remove_figure(&figure);
}
END_TEST

START_TEST(test_create_figure_false) {
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  create_figure(33, &figure);
  ck_assert(1);
}
END_TEST

START_TEST(test_replace_figure) {
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  figure_t nextFigure;
  nextFigure.matrix = malloc(sizeof(matrix_t));

  create_figure(S, &figure);

  create_figure(Z, &nextFigure);

  replace_figure(&figure, &nextFigure);

  ck_assert_int_eq(figure.matrix->rows, nextFigure.matrix->rows);
  ck_assert_int_eq(figure.matrix->columns, nextFigure.matrix->columns);

  for (int i = 0; i < figure.matrix->rows; i++) {
    for (int j = 0; j < figure.matrix->columns; j++) {
      ck_assert_int_eq(figure.matrix->matrix[i][j],
                       nextFigure.matrix->matrix[i][j]);
    }
  }

  ck_assert_int_eq(figure.x, nextFigure.x);
  ck_assert_int_eq(figure.y, nextFigure.y);

  remove_figure(&figure);
  remove_figure(&nextFigure);
}
END_TEST

START_TEST(test_generate_figure) {
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  create_figure(O, &figure);

  generate_figure(&figure);

  ck_assert_ptr_nonnull(figure.matrix);

  generate_figure(NULL);
  ck_assert(1);

  remove_figure(&figure);
}
END_TEST

START_TEST(test_move_figure_left) {
  condition_t *condition = get_current_condition();
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  matrix_t field;

  create_matrix(ROWS_FIELD, COLS_FIELD, &field);
  create_figure(O, &figure);

  figure.x = 1;
  figure.y = 0;

  condition->field = &field;
  condition->figure = &figure;

  move_figure_left();

  ck_assert_int_eq(figure.x, 0);

  remove_matrix(&field);
  remove_figure(&figure);
}
END_TEST

START_TEST(test_move_figure_left_blocked_by_wall) {
  condition_t *condition = get_current_condition();
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  matrix_t field;

  create_matrix(ROWS_FIELD, COLS_FIELD, &field);
  create_figure(O, &figure);

  figure.x = 0;
  figure.y = 0;

  condition->field = &field;
  condition->figure = &figure;

  move_figure_left();

  ck_assert_int_eq(figure.x, 0);

  remove_matrix(&field);
  remove_figure(&figure);
}
END_TEST

START_TEST(test_move_figure_left_blocked_by_figure) {
  condition_t *condition = get_current_condition();
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  matrix_t field;

  create_matrix(ROWS_FIELD, COLS_FIELD, &field);
  create_figure(O, &figure);

  figure.x = 1;
  figure.y = 0;

  field.matrix[0][0] = 1;

  condition->field = &field;
  condition->figure = &figure;

  move_figure_left();

  ck_assert_int_eq(figure.x, 1);

  remove_matrix(&field);
  remove_figure(&figure);
}
END_TEST

START_TEST(test_move_figure_right) {
  condition_t *condition = get_current_condition();
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  matrix_t field;

  create_matrix(ROWS_FIELD, COLS_FIELD, &field);
  create_figure(O, &figure);

  figure.x = 0;
  figure.y = 0;

  condition->field = &field;
  condition->figure = &figure;

  move_figure_right();

  ck_assert_int_eq(figure.x, 1);

  remove_matrix(&field);
  remove_figure(&figure);
}
END_TEST

START_TEST(test_move_figure_right_blocked_by_wall) {
  condition_t *condition = get_current_condition();
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  matrix_t field;

  create_matrix(ROWS_FIELD, COLS_FIELD, &field);
  create_figure(O, &figure);

  figure.x = COLS_FIELD - 2;
  figure.y = 0;

  condition->field = &field;
  condition->figure = &figure;

  move_figure_right();

  ck_assert_int_eq(figure.x, COLS_FIELD - 2);

  remove_matrix(&field);
  remove_figure(&figure);
}
END_TEST

START_TEST(test_move_figure_right_blocked_by_figure) {
  condition_t *condition = get_current_condition();
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  matrix_t field;

  create_matrix(ROWS_FIELD, COLS_FIELD, &field);
  create_figure(O, &figure);

  figure.x = 0;
  figure.y = 0;

  field.matrix[0][1] = 1;

  condition->field = &field;
  condition->figure = &figure;

  move_figure_right();

  ck_assert_int_eq(figure.x, 0);

  remove_matrix(&field);
  remove_figure(&figure);
}
END_TEST

START_TEST(test_move_figure_down) {
  condition_t *condition = get_current_condition();
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  matrix_t field;
  create_matrix(ROWS_FIELD, COLS_FIELD, &field);
  create_figure(O, &figure);

  figure.x = 0;
  figure.y = 0;

  condition->field = &field;
  condition->figure = &figure;

  int result = move_figure_down();

  ck_assert_int_eq(figure.y, 1);
  ck_assert_int_eq(result, 1);

  remove_matrix(&field);
  remove_figure(&figure);
}
END_TEST

START_TEST(test_move_figure_down_blocked_by_wall) {
  condition_t *condition = get_current_condition();
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  matrix_t field;

  create_matrix(ROWS_FIELD, COLS_FIELD, &field);
  create_figure(O, &figure);

  figure.x = 0;
  figure.y = ROWS_FIELD - 2;

  condition->field = &field;
  condition->figure = &figure;

  int result = move_figure_down();

  ck_assert_int_eq(figure.y, ROWS_FIELD - 2);
  ck_assert_int_eq(result, 0);

  remove_matrix(&field);
  remove_figure(&figure);
}
END_TEST

START_TEST(test_move_figure_down_blocked_by_figure) {
  condition_t *condition = get_current_condition();
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  matrix_t field;

  create_matrix(ROWS_FIELD, COLS_FIELD, &field);
  create_figure(O, &figure);

  figure.x = 0;
  figure.y = 0;

  field.matrix[1][0] = 1;

  condition->field = &field;
  condition->figure = &figure;

  int result = move_figure_down();

  ck_assert_int_eq(figure.y, 0);
  ck_assert_int_eq(result, 0);

  remove_matrix(&field);
  remove_figure(&figure);
}
END_TEST

START_TEST(test_move_figure_all_down) {
  condition_t *condition = get_current_condition();
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  matrix_t field;

  create_matrix(ROWS_FIELD, COLS_FIELD, &field);
  create_figure(O, &figure);

  figure.x = 0;
  figure.y = 0;

  condition->field = &field;
  condition->figure = &figure;

  move_figure_all_down();

  ck_assert_int_eq(figure.y, ROWS_FIELD - 2);

  remove_matrix(&field);
  remove_figure(&figure);
}
END_TEST

START_TEST(test_turn_figure_valid) {
  condition_t *condition = get_current_condition();
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  matrix_t field;

  create_matrix(ROWS_FIELD, COLS_FIELD, &field);
  create_figure(I, &figure);

  figure.x = 6;
  figure.y = 6;

  condition->field = &field;
  condition->figure = &figure;

  turn_figure();

  ck_assert_int_eq(condition->figure->matrix->matrix[0][2], 1);
  ck_assert_int_eq(condition->figure->matrix->matrix[1][2], 1);
  ck_assert_int_eq(condition->figure->matrix->matrix[2][2], 1);
  ck_assert_int_eq(condition->figure->matrix->matrix[3][2], 1);

  remove_matrix(&field);
  remove_figure(&figure);
}
END_TEST

START_TEST(test_turn_figure_invalid) {
  condition_t *condition = get_current_condition();
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  matrix_t field;

  create_matrix(ROWS_FIELD, COLS_FIELD, &field);
  create_figure(O, &figure);

  figure.x = 2;
  figure.y = 0;

  for (int i = 0; i < 10; i++) {
    field.matrix[0][i] = 1;
  }

  condition->field = &field;
  condition->figure = &figure;

  turn_figure();

  ck_assert_int_eq(figure.x, 2);

  remove_matrix(&field);
  remove_figure(&figure);
}
END_TEST

START_TEST(test_add_figure_on_field) {
  condition_t *condition = get_current_condition();
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  matrix_t field;

  create_matrix(ROWS_FIELD, COLS_FIELD, &field);
  create_figure(O, &figure);

  figure.x = 0;
  figure.y = 0;

  condition->field = &field;
  condition->figure = &figure;

  add_figure_on_field();

  ck_assert_int_eq(field.matrix[0][0], 1);
  ck_assert_int_eq(field.matrix[0][1], 1);
  ck_assert_int_eq(field.matrix[1][0], 1);
  ck_assert_int_eq(field.matrix[1][1], 1);

  remove_matrix(&field);
  remove_figure(&figure);
}
END_TEST

START_TEST(test_add_figure_on_field_out_of_bounds) {
  condition_t *condition = get_current_condition();
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  matrix_t field;

  create_matrix(ROWS_FIELD, COLS_FIELD, &field);
  create_figure(O, &figure);

  figure.x = -1;
  figure.y = -1;

  condition->field = &field;
  condition->figure = &figure;

  add_figure_on_field();

  ck_assert_int_eq(condition->field->matrix[0][0], 1);
  remove_figure_on_field();
  ck_assert_int_eq(condition->field->matrix[0][0], 0);

  remove_matrix(&field);
  remove_figure(&figure);
}
END_TEST

START_TEST(test_spawn) {
  condition_t *condition = get_current_condition();
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  figure_t nextFigure;
  nextFigure.matrix = malloc(sizeof(matrix_t));
  matrix_t field;

  create_matrix(ROWS_FIELD, COLS_FIELD, &field);
  create_figure(O, &figure);
  create_figure(I, &nextFigure);

  condition->field = &field;
  condition->figure = &figure;
  condition->nextFigure = &nextFigure;

  spawn();

  ck_assert_int_eq(figure.matrix->rows, nextFigure.matrix->rows);
  ck_assert_int_eq(figure.matrix->columns, nextFigure.matrix->columns);

  ck_assert_ptr_nonnull(nextFigure.matrix);

  remove_matrix(&field);
  remove_figure(&figure);
  remove_figure(&nextFigure);
}
END_TEST

START_TEST(test_fix_figure_valid) {
  condition_t *condition = get_current_condition();
  figure_t figure;
  figure.matrix = malloc(sizeof(matrix_t));
  matrix_t field;

  create_matrix(ROWS_FIELD, COLS_FIELD, &field);
  create_figure(L, &figure);

  figure.x = -2;
  figure.y = 5;

  condition->field = &field;
  condition->figure = &figure;

  fix_figure(&figure);

  ck_assert_int_eq(figure.x, -1);

  remove_matrix(&field);
  remove_figure(&figure);
}
END_TEST

// Вспомогательная функция для очистки состояния
void teardown_condition(void) {
  condition_t *condition = get_current_condition();
  remove_matrix(condition->field);
  free(condition->field);
  remove_figure(condition->figure);
  free(condition->figure->matrix);
  free(condition->figure);
  remove_figure(condition->nextFigure);
  free(condition->nextFigure->matrix);
  free(condition->nextFigure);
}

// Тесты для check_and_clear_rows
START_TEST(test_check_and_clear_rows_empty_field) {
  condition_t *condition = get_current_condition();
  condition->field = malloc(sizeof(matrix_t));
  create_matrix(ROWS_FIELD, COLS_FIELD, condition->field);

  // Поле пустое
  for (int i = 0; i < ROWS_FIELD; i++) {
    for (int j = 0; j < COLS_FIELD; j++) {
      condition->field->matrix[i][j] = 0;
    }
  }

  int result = check_and_clear_rows();
  ck_assert_int_eq(result, 0);  // Не должно быть удалённых рядов

  remove_matrix(condition->field);
}
END_TEST

START_TEST(test_check_and_clear_rows_one_filled_row) {
  condition_t *condition = get_current_condition();
  condition->field = malloc(sizeof(matrix_t));
  create_matrix(ROWS_FIELD, COLS_FIELD, condition->field);

  // Заполняем нижнюю строку
  for (int j = 0; j < COLS_FIELD; j++) {
    condition->field->matrix[ROWS_FIELD - 1][j] = 1;
  }

  int result = check_and_clear_rows();
  ck_assert_int_eq(result, 1);  // Должен удалить один ряд
  for (int j = 0; j < COLS_FIELD; j++) {
    ck_assert_int_eq(condition->field->matrix[ROWS_FIELD - 1][j],
                     0);  // Строка очищена
  }

  remove_matrix(condition->field);
}
END_TEST

// Тесты для check_score
START_TEST(test_check_score_single_line) {
  condition_t *condition = get_current_condition();

  condition->score = 0;
  check_score(1);
  ck_assert_int_eq(condition->score, 100);
}
END_TEST

START_TEST(test_check_score_any_lines) {
  condition_t *condition = get_current_condition();

  condition->score = 0;
  check_score(4);
  ck_assert_int_eq(condition->score, 1500);
  ck_assert_int_eq(condition->high_score, 1500);

  check_score(3);
  ck_assert_int_eq(condition->score, 2200);
  ck_assert_int_eq(condition->high_score, 2200);

  check_score(2);
  ck_assert_int_eq(condition->score, 2500);
  ck_assert_int_eq(condition->high_score, 2500);
}
END_TEST

// Тесты для check_level
START_TEST(test_check_level_initial) {
  condition_t *condition = get_current_condition();
  condition->score = 0;
  check_level();
  ck_assert_int_eq(condition->level, 1);
}
END_TEST

START_TEST(test_check_level_max) {
  init_condition();
  condition_t *condition = get_current_condition();

  condition->score = 6000;
  check_level();
  ck_assert_int_eq(condition->level, 10);
  clean_condition();
}
END_TEST

START_TEST(test_check_filled_row_full) {
  init_condition();

  int result = check_filled_row(0);
  ck_assert_int_eq(result, 0);

  clean_condition();
}
END_TEST

START_TEST(test_check_filled_row_partial) {
  init_condition();

  int result = check_filled_row(0);
  ck_assert_int_eq(result, 0);
  clean_condition();
}
END_TEST

START_TEST(test_move) {
  init_condition();
  condition_t *condition = get_current_condition();
  add_figure_on_field();
  move_left();
  ck_assert_int_eq(condition->status, MovingG);

  move_right();
  ck_assert_int_eq(condition->status, MovingG);

  move_down();
  ck_assert_int_eq(condition->status, MovingG);

  clean_condition();
}
END_TEST

START_TEST(test_move_down_to_attach) {
  init_condition();
  condition_t *condition = get_current_condition();
  add_figure_on_field();
  move_all_down();
  ck_assert_int_eq(condition->status, AttachingG);

  clean_condition();
}
END_TEST

START_TEST(test_check_lose) {
  init_condition();
  condition_t *condition = get_current_condition();

  condition->field->matrix[0][0] = 1;
  int result = check_lose();
  ck_assert_int_eq(result, 1);

  clean_condition();
}
END_TEST

START_TEST(test_turn) {
  init_condition();
  condition_t *condition = get_current_condition();
  add_figure_on_field();
  turn();
  ck_assert_int_eq(condition->status, MovingG);

  remove_figure(condition->figure);
  remove_matrix(condition->field);
  clean_condition();
}
END_TEST

START_TEST(test_game_over) {
  init_condition();
  game_over();
  clean_condition();
}
END_TEST

START_TEST(test_start_game) {
  start_game();
  condition_t *condition = get_current_condition();
  ck_assert_int_eq(condition->status, MovingG);
  condition->status = PauseG;
  start_game();
  ck_assert_int_eq(condition->status, MovingG);
  clean_condition();
}
END_TEST

START_TEST(test_update_current_state) {
  init_condition();
  GameInfo_t game_info = updateCurrentState();
  condition_t *condition = get_current_condition();
  ck_assert_int_eq(condition->score, game_info.score);
  ck_assert_int_eq(condition->level, game_info.level);
  clean_condition();
}
END_TEST

START_TEST(test_actions) {
  init_condition();
  userInput(Start, 0);
  userInput(Left, 0);
  userInput(Right, 0);
  userInput(Pause, 0);
  userInput(Pause, 0);
  userInput(Action, 0);
  userInput(Down, 1);
  userInput(Down, 0);
  clean_condition();
}
END_TEST

Suite *tetris(void) {
  Suite *suite = suite_create("backend_tests");

  TCase *matrix_case = tcase_create("matrix_test");
  tcase_add_test(matrix_case, create_test);
  tcase_add_test(matrix_case, remove_test);
  tcase_add_test(matrix_case, turn_left_test);
  tcase_add_test(matrix_case, turn_right_test);

  TCase *figure_case = tcase_create("figure_test");
  tcase_add_test(figure_case, test_create_figure_O);
  tcase_add_test(figure_case, test_create_figure_I);
  tcase_add_test(figure_case, test_create_figure_S);
  tcase_add_test(figure_case, test_create_figure_Z);
  tcase_add_test(figure_case, test_create_figure_L);
  tcase_add_test(figure_case, test_create_figure_J);
  tcase_add_test(figure_case, test_create_figure_T);
  tcase_add_test(figure_case, test_create_figure_false);
  tcase_add_test(figure_case, test_replace_figure);
  tcase_add_test(figure_case, test_generate_figure);
  tcase_add_test(figure_case, test_move_figure_left);
  tcase_add_test(figure_case, test_move_figure_left_blocked_by_wall);
  tcase_add_test(figure_case, test_move_figure_left_blocked_by_figure);
  tcase_add_test(figure_case, test_move_figure_right);
  tcase_add_test(figure_case, test_move_figure_right_blocked_by_wall);
  tcase_add_test(figure_case, test_move_figure_right_blocked_by_figure);
  tcase_add_test(figure_case, test_move_figure_down);
  tcase_add_test(figure_case, test_move_figure_down_blocked_by_wall);
  tcase_add_test(figure_case, test_move_figure_down_blocked_by_figure);
  tcase_add_test(figure_case, test_move_figure_all_down);
  tcase_add_test(figure_case, test_turn_figure_valid);
  tcase_add_test(figure_case, test_turn_figure_invalid);
  tcase_add_test(figure_case, test_add_figure_on_field);
  tcase_add_test(figure_case, test_add_figure_on_field_out_of_bounds);
  tcase_add_test(figure_case, test_spawn);
  tcase_add_test(figure_case, test_fix_figure_valid);

  TCase *fsm_case = tcase_create("fsm_test");
  tcase_add_test(fsm_case, test_check_and_clear_rows_empty_field);
  tcase_add_test(fsm_case, test_check_and_clear_rows_one_filled_row);
  tcase_add_test(fsm_case, test_check_score_single_line);
  tcase_add_test(fsm_case, test_check_score_any_lines);
  tcase_add_test(fsm_case, test_check_level_initial);
  tcase_add_test(fsm_case, test_check_level_max);
  tcase_add_test(fsm_case, test_check_filled_row_full);
  tcase_add_test(fsm_case, test_check_filled_row_partial);
  tcase_add_test(fsm_case, test_move);
  tcase_add_test(fsm_case, test_move_down_to_attach);
  tcase_add_test(fsm_case, test_check_lose);
  tcase_add_test(fsm_case, test_turn);
  tcase_add_test(fsm_case, test_game_over);
  tcase_add_test(fsm_case, test_start_game);
  tcase_add_test(fsm_case, test_update_current_state);
  tcase_add_test(fsm_case, test_actions);

  suite_add_tcase(suite, matrix_case);
  suite_add_tcase(suite, figure_case);
  suite_add_tcase(suite, fsm_case);
  return suite;
}

int main(void) {
  Suite *s;
  int number_failed;
  s = tetris();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}