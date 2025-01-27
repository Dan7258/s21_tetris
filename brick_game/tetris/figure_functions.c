#include "brick_game.h"

void s21_create_figure(SelectedFigure_t SelectedFigure, figure_t *figure) {
  figure->matrix = (matrix_t *)malloc(sizeof(matrix_t));
  switch (SelectedFigure) {
  case O:
    s21_create_O(figure);
    break;
  case I:
    s21_create_I(figure);
    break;
  case S:
    s21_create_S(figure);
    break;
  case Z:
    s21_create_Z(figure);
    break;
  case L:
    s21_create_L(figure);
    break;
  case J:
    s21_create_J(figure);
    break;
  case T:
    s21_create_T(figure);
    break;
  }
}

void s21_remove_figure(figure_t *figure) {
  if(figure->matrix != NULL) {
    s21_remove_matrix(figure->matrix);
    // figure->matrix = NULL;
  }
}

void s21_generate_figure(figure_t *figure) {
  s21_remove_figure(figure);
  SelectedFigure_t select = rand() % 7;
  s21_create_figure(select, figure);
}

void s21_replace_figure(figure_t *figure, figure_t *nextFigure) {
  s21_remove_figure(figure);
  s21_create_matrix(nextFigure->matrix->rows, nextFigure->matrix->columns, figure->matrix);
  s21_copy_matrix(nextFigure->matrix, figure->matrix);
  figure->x = nextFigure->x;
  figure->y = nextFigure->y;
}

void s21_create_O(figure_t *figure) {
  s21_create_matrix(2, 2, figure->matrix);

  figure->matrix->matrix[0][0] = 1;
  figure->matrix->matrix[0][1] = 1;
  figure->matrix->matrix[1][0] = 1;
  figure->matrix->matrix[1][1] = 1;

  figure->x = 4;
  figure->y = -2;
}

void s21_create_I(figure_t *figure) {
  s21_create_matrix(4, 4, figure->matrix);
  
  figure->matrix->matrix[2][0] = 1;
  figure->matrix->matrix[2][1] = 1;
  figure->matrix->matrix[2][2] = 1;
  figure->matrix->matrix[2][3] = 1;

  figure->x = 3;
  figure->y = -3;
}

void s21_create_S(figure_t *figure) {
  s21_create_matrix(3, 3, figure->matrix);
  
  figure->matrix->matrix[0][0] = 1;
  figure->matrix->matrix[1][0] = 1;
  figure->matrix->matrix[1][1] = 1;
  figure->matrix->matrix[2][1] = 1;

  figure->x = 4;
  figure->y = -3;
}

void s21_create_Z(figure_t *figure) {
  s21_create_matrix(3, 3, figure->matrix);
  
  figure->matrix->matrix[0][1] = 1;
  figure->matrix->matrix[1][1] = 1;
  figure->matrix->matrix[1][0] = 1;
  figure->matrix->matrix[2][0] = 1;

  figure->x = 4;
  figure->y = -3;
}

void s21_create_L(figure_t *figure) {
  s21_create_matrix(3, 3, figure->matrix);
  
  figure->matrix->matrix[0][1] = 1;
  figure->matrix->matrix[1][1] = 1;
  figure->matrix->matrix[2][1] = 1;
  figure->matrix->matrix[2][2] = 1;
  
  figure->x = 3;
  figure->y = -3;
}

void s21_create_J(figure_t *figure) {
  s21_create_matrix(3, 3, figure->matrix);
  
  figure->matrix->matrix[0][2] = 1;
  figure->matrix->matrix[1][2] = 1;
  figure->matrix->matrix[2][2] = 1;
  figure->matrix->matrix[2][1] = 1;

  figure->x = 3;
  figure->y = -3;
}

void s21_create_T(figure_t *figure) {
  s21_create_matrix(3, 3, figure->matrix);
  
  figure->matrix->matrix[1][0] = 1;
  figure->matrix->matrix[1][1] = 1;
  figure->matrix->matrix[1][2] = 1;
  figure->matrix->matrix[2][1] = 1;

  figure->x = 4;
  figure->y = -3;
}

void s21_move_figure_left() {
  int flag = 1;
  condition_t *condition = s21_get_current_condition();
  for(int m = 0; m < condition->figure->matrix->rows && flag; m++) {
    for(int n = 0; n < condition->figure->matrix->columns && flag; n++) {
      if(condition->figure->matrix->matrix[m][n] && n + condition->figure->x - 1 < 0) {
        flag = 0;
      } 
      if(n + condition->figure->x - 1 > COLS_FIELD - 1) {
        continue;
      } else if(flag && condition->figure->matrix->matrix[m][n] && condition->field->matrix[m + condition->figure->y][n + condition->figure->x - 1]) {
        flag = 0;
      }
    }
  }

  condition->figure->x = flag ? condition->figure->x - 1 : condition->figure->x;
}

void s21_move_figure_right() {
  int flag = 1;
  condition_t *condition = s21_get_current_condition();
  for(int m = 0; m < condition->figure->matrix->rows && flag; m++) {
    for(int n = 0; n < condition->figure->matrix->columns && flag; n++) {
      if(condition->figure->matrix->matrix[m][n] && n + condition->figure->x + 1 > COLS_FIELD - 1) {
        flag = 0;
      }
      if(n + condition->figure->x + 1 < 0) {
        continue;
      } else if(flag && condition->figure->matrix->matrix[m][n] && condition->field->matrix[m + condition->figure->y][n + condition->figure->x + 1]) {
        flag = 0;
      }
    }
  }

  condition->figure->x = flag ? condition->figure->x + 1 : condition->figure->x;
}

int s21_move_figure_down() {
  int flag = 1;
  condition_t *condition = s21_get_current_condition();
  for(int m = 0; m < condition->figure->matrix->rows && flag; m++) {
    for(int n = 0; n < condition->figure->matrix->columns && flag; n++) {
      if(condition->figure->matrix->matrix[m][n] && m + condition->figure->y + 1 > ROWS_FIELD - 1) {
        flag = 0;
      }
      if(m + condition->figure->y + 1 < 0) {
        continue;
      } else if(flag && condition->figure->matrix->matrix[m][n] && condition->field->matrix[m + condition->figure->y + 1][n + condition->figure->x]) {
        flag = 0;
      }
    }
  }

  condition->figure->y = flag ? condition->figure->y + 1 : condition->figure->y;
  return flag;
}

void s21_move_figure_all_down() {
  for(;s21_move_figure_down;) {
  }
}

void s21_turn_figure() {
  condition_t *condition = s21_get_current_condition();
  s21_turn_matrix(condition->figure->matrix);
}

void s21_add_figure_on_field() {
  condition_t *condition = s21_get_current_condition();
  for (int m = 0; m < condition->figure->matrix->rows; m++) {
    for (int n = 0; n < condition->figure->matrix->columns; n++) {
      if(m + condition->figure->y >= 0 && condition->figure->matrix->matrix[m][n]) {
        condition->field->matrix[m + condition->figure->y][n + condition->figure->x] = 1;
      }
    }
  }
}

void s21_remove_figure_on_field() {
  condition_t *condition = s21_get_current_condition();
  for (int m = 0; m < condition->figure->matrix->rows; m++) {
    for (int n = 0; n < condition->figure->matrix->columns; n++) {
      if(m + condition->figure->y >= 0 && condition->figure->matrix->matrix[m][n]) {
        condition->field->matrix[m + condition->figure->y][n + condition->figure->x] = 0;
      }
    }
  }
}

int s21_check_and_clear_rows() {
  condition_t *condition = s21_get_current_condition();
  int f = 0;
  int counter = 0;
  for (int m = 0; m < ROWS_FIELD; m++) {
    if(s21_check_filled_row(m)) {
      counter++;
      for (;s21_check_filled_row(f) && f < ROWS_FIELD; f++) {
      }
      for (int n = 0; n < COLS_FIELD; n++) {
        if(f >= ROWS_FIELD) {
          condition->field->matrix[m][n] = 0;
        } else {
          condition->field->matrix[m][n] = condition->field->matrix[f][n];
        }
      }
    }
    f++;
  }
  return counter;
}

int s21_check_filled_row(int m) {
  condition_t *condition = s21_get_current_condition();
  int flag = 1;
  for (int n = 0; n < COLS_FIELD && flag; n++) {
    flag = !(condition->field->matrix[m][n]) ? 0 : flag;
  }
  return flag;
}
