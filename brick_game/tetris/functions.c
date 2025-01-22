#include "brick_game.h"

void s21_create_matrix(int rows, int columns, matrix_t *result) {
  result->rows = rows;
  result->columns = columns;
  result->matrix = (double **)malloc(rows * sizeof(double *));
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)calloc(columns, sizeof(double));
  }
}

void s21_remove_matrix(matrix_t *M) {
  for (int m = 0; m < M->rows; m++) {
    free(M->matrix[m]);
  }
  free(M->matrix);
  M->matrix = NULL;
}

void s21_turn_matrix(matrix_t *M) {
  matrix_t copy_m = {0};
  s21_copy_matrix(M, &copy_m);
  for(int m = 0; m < M -> rows; m++) {
    for(int n = 0; n < M -> columns; n++) {
      M->matrix[m][n] = copy_m.matrix[n][(m - (M -> rows - 1)) * -1];
    }
  }
  s21_remove_matrix(&copy_m);
}

void s21_copy_matrix(matrix_t *M, matrix_t *result) {
  s21_create_matrix(M->rows, M->columns, result);
  for(int m = 0; m < result -> rows; m++) {
    for(int n = 0; n < result -> columns; n++) {
      result->matrix[m][n] = M->matrix[m][n];
    }
  }
}

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