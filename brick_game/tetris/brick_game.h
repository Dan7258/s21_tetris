#ifndef BRICK_GAME_H
#define BRICK_GAME_H

#define ROWS_FIELD 20
#define COLS_FIELD 10
#define MAX_LEVEL 10

#include <stdio.h>
#include <stdlib.h>

typedef struct figure {
  matrix_t *matrix;
  int x;
  int y;
} figure_t;

typedef struct matrix {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

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

//matrix functions
void s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *M);
void s21_turn_matrix(matrix_t *M);
void s21_copy_matrix(matrix_t *M, matrix_t *result);

//figure functions
void s21_create_figure(SelectedFigure_t SelectedFigure, figure_t *figure);
void s21_remove_figure(figure_t *figure);
void s21_create_O(figure_t *figure); 
void s21_create_I(figure_t *figure);
void s21_create_S(figure_t *figure);
void s21_create_Z(figure_t *figure);
void s21_create_L(figure_t *figure);
void s21_create_J(figure_t *figure);
void s21_create_T(figure_t *figure);
void move_figure_left(matrix_t *field, figure_t *figure);
void move_figure_right(matrix_t *field, figure_t *figure);
int move_figure_down(matrix_t *field, figure_t *figure);
void add_figure_on_field(matrix_t *field, figure_t *figure);
void remove_figure_on_field(matrix_t *field, figure_t *figure);


#endif