#ifndef API_H
#define API_H

#define ROWS_FIELD 20
#define COLS_FIELD 10
#define ROWS_NEXT 5
#define COLS_NEXT 5
#define MAX_LEVEL 10

#include <stdbool.h>

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

// API functions
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

#endif