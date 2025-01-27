#include "brick_game.h"

int main() {
  setlocale(LC_ALL, "ru_RU.UTF-8");
  initscr();              
  cbreak();               
  noecho();
  game_loop();
  // GameInfo_t gameInfo = {0};
  // gameInfo.score = 123456789;
  // gameInfo.high_score = 123456789;
  // s21_print_owerlay(gameInfo);
  getch();
  endwin();
  
  return 0;
}

void game_loop() {
  s21_print_owerlay(updateCurrentState());
  userInput(getAct(), true);
  for(;;) {
    s21_print_owerlay(updateCurrentState());
    userInput(getAct(), true);
  }

}

UserAction_t getAct() {
  UserAction_t action;
  switch (getch()) {
  case 10:
    action = Start;
    break;
  case 27:
    action = Pause;
    break;
  case 17:
    action = Up;
    break;
  case 18:
    action = Left;
    break;
  case 19:
    action = Right;
    break;
  case 14:
    action = Down;
  case 32:
    action = Action;
    break;
  default:
    action = Up;
    break;
  }
  return action;
}

void userInput(UserAction_t action, bool hold) {
  srand(time(NULL));
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
  if(condition->status == MovingG) {
    s21_move_down();
  }
  condition = s21_get_current_condition();
  if(condition->status == AttachingG) {
    s21_check_and_clear_rows();
    if(s21_check_lose()) {
      condition->status = GameOverG;
    }
  }
}

GameInfo_t updateCurrentState() {
  condition_t *condition = s21_get_current_condition();
  if(condition->status == InitG) {
    s21_init_condition();
  }
  GameInfo_t info = {0};
  // if(condition->field == NULL) {
  //   printf("null field\n");
  // }
  info.field = condition->field->matrix;
  info.next = condition->nextFigure->matrix->matrix;
  info.score = 0;
  info.high_score = 0;
  info.level = 0;
  info.speed = 0;
  info.pause = 0;
  return info;
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
    s21_move_figure_down();
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
}

void s21_start_game() {
  condition_t *condition = s21_get_current_condition();
  s21_create_matrix(ROWS_FIELD, COLS_FIELD, condition->field);
  s21_generate_figure(condition->figure);
  s21_generate_figure(condition->nextFigure);
  condition->status = Start;
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
  condition->status = Start;
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
    if(condition->field->matrix[0][m]) {
      flag = 1;
    }
  }
  return flag;
}

void s21_spawn() {
  condition_t *condition = s21_get_current_condition();
  s21_replace_figure(condition->figure, condition->nextFigure);
  s21_generate_figure(condition->nextFigure);
}



