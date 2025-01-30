#ifndef BRICK_GAME_H
#define BRICK_GAME_H

#define ROWS_FIELD 20
#define COLS_FIELD 10
#define ROWS_NEXT 5
#define COLS_NEXT 5
#define MAX_LEVEL 10

#include <stdbool.h>
#include <stdio.h>
#include <ncurses.h>

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

//API functions
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

//game funtions
UserAction_t getAct();
void game_loop();
int s21_check_end_game(GameInfo_t info);
void s21_clear_memory(GameInfo_t *info);

#endif