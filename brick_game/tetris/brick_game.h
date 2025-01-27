#ifndef BRICK_GAME_H
#define BRICK_GAME_H

#define ROWS_FIELD 20
#define COLS_FIELD 10
#define MAX_LEVEL 10

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h> 
#include <ncurses.h>
#include <locale.h>

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

typedef enum {
  O = 0,
  I,
  S,
  Z,
  L,
  J,
  T
} SelectedFigure_t;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef enum {
  Start = 0,
  Spawn,
  Moving,
  Shifting,
  Attaching,
  GameOver
} GameStatus_t;

typedef struct condition {
  matrix_t *field;
  matrix_t *figure;
  matrix_t *nextFigure;
  GameStatus_t status;
} condition_t;

//matrix functions
void s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *M);
void s21_turn_matrix(matrix_t *M);
void s21_copy_matrix(matrix_t *M, matrix_t *result);

//figure functions
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
void s21_move_figure_left(matrix_t *field, figure_t *figure);
void s21_move_figure_right(matrix_t *field, figure_t *figure);
int s21_move_figure_down(matrix_t *field, figure_t *figure);
void s21_add_figure_on_field(matrix_t *field, figure_t *figure);
void s21_remove_figure_on_field(matrix_t *field, figure_t *figure);
int s21_check_and_clear_rows(matrix_t *field);
int s21_check_filled_row(int m, matrix_t *field);
int s21_check_lose(matrix_t *field);
void s21_game_over(matrix_t *field, figure_t *figure, figure_t *nextFigure);

// fsm functions
// void userInput(UserAction_t action, bool hold);
// GameInfo_t updateCurrentState();
// void game_init(GameInfo_t game);


void game_loop();
void s21_generate_figure(figure_t *figure);
void s21_spawn(matrix_t *field, figure_t *figure, figure_t *nextFigure);
int s21_moving(matrix_t *field, figure_t *figure, UserAction_t action);
void s21_shift(matrix_t *field, figure_t *figure, UserAction_t action);

void s21_print_owerlay(GameInfo_t gameInfo);
void s21_print_frame();
void s21_print_field(GameInfo_t gameInfo);
void s21_print_next_figure(GameInfo_t gameInfo);
void s21_print_score(GameInfo_t gameInfo);
void s21_print_high_score(GameInfo_t gameInfo);
void s21_print_level(GameInfo_t gameInfo);

#endif