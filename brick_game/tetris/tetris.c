#include "brick_game.h"

int main() {
  setlocale(LC_ALL, "ru_RU.UTF-8");
  initscr();              
  cbreak();               
  noecho();
  // nodelay(stdscr, TRUE); 
  game_loop();
  getch();
  endwin();
  
  return 0;
}

void game_loop() {
  // s21_print_start_menu();
  // UserAction_t action = getAct();
  UserAction_t action = Start;
  updateCurrentState();
  // !s21_check_lose(updateCurrentState())
  for(;;) {
    userInput(action, true);
    s21_print_owerlay(updateCurrentState());
    action = getAct();
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
  case 'w':
    action = Up;
    break;
  case 'a':
    action = Left;
    break;
  case 'd':
    action = Right;
    break;
  case 's':
    action = Down;
    break;
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
    mvprintw(15, 30, "%d", condition->status);
    s21_move_down();
  }
  if(condition->status == AttachingG) {
    s21_check_and_clear_rows();
    if(!s21_check_lose(updateCurrentState())) {
      s21_spawn();
    }
  }
  mvprintw(15, 30, "%d", condition->status);
}

GameInfo_t updateCurrentState() {
  condition_t *condition = s21_get_current_condition();
  if(condition->status == InitG) {
    srand(time(NULL));
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

int s21_check_lose(GameInfo_t info) {
  int flag = 0;
  for (int m = 0; m < COLS_FIELD && !flag; m++) {
    if(info.field[0][m]) {
      flag = 1;
    }
  }
  return flag;
}

void s21_spawn() {
  condition_t *condition = s21_get_current_condition();
  s21_replace_figure(condition->figure, condition->nextFigure);
  s21_generate_figure(condition->nextFigure);
  condition->status = MovingG;
}



