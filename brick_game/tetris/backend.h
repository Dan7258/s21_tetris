#ifndef BACKEND_H
#define BACKEND_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../tetris.h"

typedef struct matrix {
  int **matrix;
  int rows;
  int columns;
} matrix_t;

typedef struct figure {
  matrix_t *matrix;
  int x;
  int y;
} figure_t;

typedef enum { O = 0, I, S, Z, L, J, T } SelectedFigure_t;

typedef enum {
  InitG,
  StartG,
  PauseG,
  MovingG,
  AttachingG,
  GameOverG
} GameStatus_t;

typedef struct condition {
  matrix_t *field;
  figure_t *figure;
  figure_t *nextFigure;
  GameStatus_t status;
  unsigned long time;
  unsigned long interval;
  int score;
} condition_t;

// matrix functions
void s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *M);
void s21_turn_left_matrix(matrix_t *M);
void s21_turn_right_matrix(matrix_t *M);
void s21_copy_matrix(matrix_t *M, matrix_t *result);

// figure functions
void s21_create_figure(SelectedFigure_t SelectedFigure, figure_t *figure);
void s21_remove_figure(figure_t *figure);
void s21_generate_figure(figure_t *figure);
void s21_replace_figure(figure_t *figure, figure_t *nextFigure);
void s21_create_O(figure_t *figure);
void s21_create_I(figure_t *figure);
void s21_create_S(figure_t *figure);
void s21_create_Z(figure_t *figure);
void s21_create_L(figure_t *figure);
void s21_create_J(figure_t *figure);
void s21_create_T(figure_t *figure);
void s21_move_figure_left();
void s21_move_figure_right();
int s21_move_figure_down();
void s21_move_figure_all_down();
void s21_turn_figure();
void s21_add_figure_on_field();
void s21_remove_figure_on_field();
void s21_spawn();
int s21_is_figure_valid(figure_t *figure);
void s21_fix_figure(figure_t *figure);

// fsm functions
int s21_check_and_clear_rows();
int s21_check_filled_row(int m);
void s21_check_score(int count);
void s21_move_left();
void s21_move_right();
void s21_move_all_down();
void s21_move_down();
void s21_turn();
void s21_init_condition();
void s21_start_game();
condition_t *s21_get_current_condition();
void s21_clean_condition();
void s21_game_over();
int s21_check_lose();
unsigned long millis();
#endif
