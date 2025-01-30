#include "backend.h"

void userInput(UserAction_t action, bool hold) {
  condition_t *condition = s21_get_current_condition();
  if(action == Start && condition->status == InitG) {
    s21_start_game();
  } else if(action == Pause && condition->status != InitG) {

  }else if(action == Terminate && condition->status != InitG) {
    s21_clean_condition();
    s21_start_game();
  }else if(action == Left && condition->status == MovingG) {
    s21_move_left();
  }else if(action == Right && condition->status == MovingG) {
    s21_move_right();
  }else if(action == Down && condition->status == MovingG) {
    s21_move_all_down();
  } else if(action == Action && condition->status == MovingG) {
    s21_turn();
  }
  if(condition->status == MovingG || action == Up) {
    if(millis() - condition->time > condition->interval) {
      s21_move_down();
      condition->time = millis();
    }
    
  }
  if(condition->status == AttachingG) {
    s21_check_and_clear_rows();
    if(!s21_check_lose()) {
      s21_spawn();
    } else {
      s21_remove_figure(condition->nextFigure);
      s21_create_matrix(5, 5, condition->nextFigure->matrix);
      for(int i = 0; i < ROWS_NEXT; i++) {
        for(int j = 0; j < COLS_NEXT; j++) {
          condition->nextFigure->matrix->matrix[i][j] = 0;
        }
      }
    }
  }
}

GameInfo_t updateCurrentState() {
  condition_t *condition = s21_get_current_condition();
  if(condition->status == InitG) {
    srand(time(NULL));
    s21_init_condition();
  }
  GameInfo_t info = {0};
  info.field = condition->field->matrix;
  info.next = (int **)malloc(ROWS_NEXT * sizeof(int *));
  for (int i = 0; i < ROWS_NEXT; i++) {
    info.next[i] = (int *)calloc(COLS_NEXT, sizeof(int));
  }
  for(int m = 0; m < condition->nextFigure->matrix-> rows; m++) {
    for(int n = 0; n < condition->nextFigure->matrix-> columns; n++) {
      info.next[m][n] = condition->nextFigure->matrix->matrix[m][n];
    }
  }
  info.score = 0;
  info.high_score = 0;
  info.level = 0;
  info.speed = 0;
  info.pause = 0;
  return info;
}

int s21_check_and_clear_rows() {
  condition_t *condition = s21_get_current_condition();
  int counter = 0;
  for (int m = ROWS_FIELD - 1; m >= 0; m--) {
    if(s21_check_filled_row(m)) {
      counter++;
      for (int f = m;f >= 0; f--) {
        for (int n = 0; n < COLS_FIELD; n++) {
          condition->field->matrix[f][n] = condition->field->matrix[f - 1][n];
        }
      }
      for (int n = 0; n < COLS_FIELD; n++) {
        condition->field->matrix[0][n] = 0;
      }
      m++;
    }
  }
  return counter;
}

int s21_check_filled_row(int m) {
  condition_t *condition = s21_get_current_condition();
  int flag = 1;
  for (int n = 0; n < COLS_FIELD && flag; n++) {
    flag = (condition->field->matrix[m][n]) ? flag : 0;
  }
  return flag;
}

void s21_move_left() {
  condition_t *condition = s21_get_current_condition();
  condition->status = MovingG;
  s21_remove_figure_on_field();
  s21_move_figure_left();
  s21_add_figure_on_field();
}

void s21_move_right() {
  condition_t *condition = s21_get_current_condition();
  condition->status = MovingG;
  s21_remove_figure_on_field();
  s21_move_figure_right();
  s21_add_figure_on_field();
}

void s21_move_all_down() {
  condition_t *condition = s21_get_current_condition();
  condition->status = AttachingG;
  s21_remove_figure_on_field();
  s21_move_figure_all_down();
  s21_add_figure_on_field();
}

void s21_move_down() {
  condition_t *condition = s21_get_current_condition();
  if(condition->status != AttachingG) {
    condition->status = MovingG;
    s21_remove_figure_on_field();
    if(!s21_move_figure_down()) {
      condition->status = AttachingG;
    }
    s21_add_figure_on_field();
  }
}

void s21_turn() {
  condition_t *condition = s21_get_current_condition();
  condition->status = MovingG;
  s21_remove_figure_on_field();
  s21_turn_figure();
  s21_add_figure_on_field();
}

void s21_init_condition() {
  condition_t *condition = s21_get_current_condition();
  condition->field = malloc(sizeof(matrix_t));
  condition->figure = malloc(sizeof(figure_t));
  condition->nextFigure = malloc(sizeof(figure_t));
  condition->figure->matrix = malloc(sizeof(matrix_t));
  condition->nextFigure->matrix = malloc(sizeof(matrix_t));
  s21_create_matrix(ROWS_FIELD, COLS_FIELD, condition->field);
  s21_generate_figure(condition->figure);
  s21_generate_figure(condition->nextFigure);
  condition->status = InitG;
  condition->time = millis();
  condition->interval = 500;
}

void s21_start_game() {
  condition_t *condition = s21_get_current_condition();
  s21_create_matrix(ROWS_FIELD, COLS_FIELD, condition->field);
  s21_generate_figure(condition->figure);
  s21_generate_figure(condition->nextFigure);
  condition->status = MovingG;
}

condition_t *s21_get_current_condition() {
  static condition_t condition;
  return &condition;
}

void s21_clean_condition() {
  condition_t *condition = s21_get_current_condition();
  s21_remove_matrix(condition->field);
  s21_remove_figure(condition->figure);
  s21_remove_figure(condition->nextFigure);
  condition->status = MovingG;
}

void s21_game_over() {
  condition_t *condition = s21_get_current_condition();
  s21_remove_matrix(condition->field);
  s21_remove_figure(condition->figure);
  s21_remove_figure(condition->nextFigure);
  condition->status = GameOverG;
}

int s21_check_lose() {
  condition_t *condition = s21_get_current_condition();
  int flag = 0;
  for (int m = 0; m < COLS_FIELD && !flag; m++) {
    if(condition->field->matrix[0][m]==1) {
      flag = 1;
    }
  }
  return flag;
}

unsigned long millis() {
  return (unsigned long)(clock() * 1000 / CLOCKS_PER_SEC);
}