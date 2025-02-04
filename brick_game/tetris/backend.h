#ifndef BACKEND_H
#define BACKEND_H

#include <stdio.h>
#include <stdlib.h>

#include "api.h"

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
  int score;
  int high_score;
  int level;
} condition_t;

// matrix functions
void create_matrix(int rows, int columns, matrix_t *result);
void remove_matrix(matrix_t *M);
void turn_left_matrix(matrix_t *M);
void turn_right_matrix(matrix_t *M);
void copy_matrix(matrix_t *M, matrix_t *result);

// figure functions
void create_figure(SelectedFigure_t SelectedFigure, figure_t *figure);
void remove_figure(figure_t *figure);
void generate_figure(figure_t *figure);
void replace_figure(figure_t *figure, figure_t *nextFigure);
void create_O(figure_t *figure);
void create_I(figure_t *figure);
void create_S(figure_t *figure);
void create_Z(figure_t *figure);
void create_L(figure_t *figure);
void create_J(figure_t *figure);
void create_T(figure_t *figure);
void move_figure_left();
void move_figure_right();
int move_figure_down();
void move_figure_all_down();
void turn_figure();
void add_figure_on_field();
void remove_figure_on_field();
void spawn();
int is_figure_valid(figure_t *figure);
void fix_figure(figure_t *figure);

// fsm functions
int check_and_clear_rows();
int check_filled_row(int m);
void check_score(int count);
void check_level();
void move_left();
void move_right();
void move_all_down();
void move_down();
void turn();
void init_condition();
void start_game();
condition_t *get_current_condition();
void clean_condition();
void game_over();
int check_lose();
int get_high_score_from_file();
void set_high_score_in_file(int high_score);
#endif
