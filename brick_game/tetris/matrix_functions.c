#include "backend.h"

void s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (result == NULL) {
    mvprintw(4, 46, "result NULL");
    refresh();
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (int *)calloc(columns, sizeof(int));
    }
  }
}

void s21_remove_matrix(matrix_t *M) {
  for (int m = 0; m < M->rows; m++) {
    free(M->matrix[m]);
  }
  free(M->matrix);
}

void s21_turn_matrix(matrix_t *M) {
  matrix_t copy_m = {0};
  s21_copy_matrix(M, &copy_m);
  for (int m = 0; m < M->rows; m++) {
    for (int n = 0; n < M->columns; n++) {
      M->matrix[m][n] = copy_m.matrix[n][(m - (M->rows - 1)) * -1];
    }
  }
  s21_remove_matrix(&copy_m);
}

void s21_copy_matrix(matrix_t *M, matrix_t *result) {
  s21_create_matrix(M->rows, M->columns, result);
  for (int m = 0; m < result->rows; m++) {
    for (int n = 0; n < result->columns; n++) {
      result->matrix[m][n] = M->matrix[m][n];
    }
  }
}
