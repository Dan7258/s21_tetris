#include "brick_game.h"

void s21_create_figure(SelectedFigure_t SelectedFigure, figure_t *figure) {
  switch (SelectedFigure) {
  case 0:
    s21_create_O(figure);
    break;
  case 1:
    s21_create_I(figure);
    break;
  case 2:
    s21_create_S(figure);
    break;
  case 3:
    s21_create_Z(figure);
    break;
  case 4:
    s21_create_L(figure);
    break;
  case 5:
    s21_create_J(figure);
    break;
  case 6:
    s21_create_T(figure);
    break;
  }
}

void s21_remove_figure(figure_t *figure) {
  s21_remove_matrix(figure->matrix);
  figure->matrix = NULL;
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

void move_figure_left(matrix_t *field, figure_t *figure) {
  int flag = 1;

  for(int m = 0; m < figure->matrix->rows && flag; m++) {
    for(int n = 0; n < figure->matrix->columns && flag; n++) {
      if(figure->matrix->matrix[m][n] && n + figure->x - 1 < 0) {
        flag = 0;
      }
      if(flag && figure->matrix->matrix[m][n] && field->matrix[m + figure->y][n + figure->x - 1]) {
        flag = 0;
      }
    }
  }

  figure->x = flag ? figure->x - 1 : figure->x;
}

void move_figure_right(matrix_t *field, figure_t *figure) {
  int flag = 1;

  for(int m = 0; m < figure->matrix->rows && flag; m++) {
    for(int n = 0; n < figure->matrix->columns && flag; n++) {
      if(figure->matrix->matrix[m][n] && n + figure->x + 1 > COLS_FIELD - 1) {
        flag = 0;
      }
      if(flag && figure->matrix->matrix[m][n] && field->matrix[m + figure->y][n + figure->x + 1]) {
        flag = 0;
      }
    }
  }

  figure->x = flag ? figure->x + 1 : figure->x;
}

int move_figure_down(matrix_t *field, figure_t *figure) {
  int flag = 1;

  for(int m = 0; m < figure->matrix->rows && flag; m++) {
    for(int n = 0; n < figure->matrix->columns && flag; n++) {
      if(figure->matrix->matrix[m][n] && m + figure->y + 1 > ROWS_FIELD - 1) {
        flag = 0;
      }
      if(flag && figure->matrix->matrix[m][n] && field->matrix[m + figure->y + 1][n + figure->x]) {
        flag = 0;
      }
    }
  }

  figure->y = flag ? figure->y + 1 : figure->y;
  return flag;
}

void add_figure_on_field(matrix_t *field, figure_t *figure) {
  for (int m = 0; m < figure->matrix->rows; m++) {
    for (int n = 0; n < figure->matrix->columns; n++) {
      if(m + figure->y > 0 && figure->matrix->matrix[m][n]) {
        field->matrix[m + figure->y][n + figure->x] = 1;
      }
    }
  }
}

void remove_figure_on_field(matrix_t *field, figure_t *figure) {
  for (int m = 0; m < figure->matrix->rows; m++) {
    for (int n = 0; n < figure->matrix->columns; n++) {
      if(m + figure->y > 0 && figure->matrix->matrix[m][n]) {
        field->matrix[m + figure->y][n + figure->x] = 0;
      }
    }
  }
}
