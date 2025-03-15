/**
 * @file matrix_functions.c
 * @brief Реализация функций для работы с матрицами.
 */
#include "backend.h"

void create_matrix(int rows, int columns, matrix_t *result) {
  if (result != NULL) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (int *)calloc(columns, sizeof(int));
    }
  }
}

void remove_matrix(matrix_t *M) {
  if (M != NULL) {
    for (int m = 0; m < M->rows; m++) {
      free(M->matrix[m]);
    }
    free(M->matrix);
    M->rows = 0;
    M->columns = 0;
    M->matrix = NULL;
  }
}

void turn_left_matrix(matrix_t *M) {
  matrix_t copy_m = {0};
  copy_matrix(M, &copy_m);
  for (int m = 0; m < M->rows; m++) {
    for (int n = 0; n < M->columns; n++) {
      M->matrix[m][n] = copy_m.matrix[n][(m - (M->rows - 1)) * -1];
    }
  }
  remove_matrix(&copy_m);
}

void turn_right_matrix(matrix_t *M) {
  matrix_t copy_m = {0};
  copy_matrix(M, &copy_m);
  for (int m = 0; m < M->rows; m++) {
    for (int n = 0; n < M->columns; n++) {
      M->matrix[m][n] = copy_m.matrix[(n - (M->columns - 1)) * -1][m];
    }
  }
  remove_matrix(&copy_m);
}

void copy_matrix(matrix_t *M, matrix_t *result) {
  create_matrix(M->rows, M->columns, result);
  for (int m = 0; m < result->rows; m++) {
    for (int n = 0; n < result->columns; n++) {
      result->matrix[m][n] = M->matrix[m][n];
    }
  }
}
