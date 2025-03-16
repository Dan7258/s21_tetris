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

  suite_add_tcase(suite, matrix_case);
  suite_add_tcase(suite, figure_case);
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