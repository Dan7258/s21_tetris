#ifndef BRICK_GAME_H
#define BRICK_GAME_H

#define ROWS_MAP 20
#define COLS_MAP 10
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

#endif