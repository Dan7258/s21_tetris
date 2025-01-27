#include "brick_game.h"

int main() {
  // setlocale(LC_ALL, "ru_RU.UTF-8");
  // initscr();              
  // cbreak();               
  // noecho();
  // // clear();
  // GameInfo_t gameInfo = {0};
  // gameInfo.score = 123456789;
  // gameInfo.high_score = 123456789;
  // s21_print_owerlay(gameInfo);
  // getch();
  // endwin();
  game_loop();
  return 0;
}

void game_loop() {
  srand(time(NULL));
  matrix_t field = {0};
  figure_t figure = {0};
  figure_t nextFigure = {0};

  s21_create_matrix(ROWS_FIELD, COLS_FIELD, &field);
  s21_generate_figure(&figure);
  s21_generate_figure(&nextFigure);

  int breakFlag = 1;
  int attaching = 1;
  UserAction_t action;

  // clock_t startTime = clock();
  // clock_t currentTime;
  // int paramTime = 500;

  for(;;) {
    // currentTime = clock();
    // if(((double)(currentTime - startTime) / CLOCKS_PER_SEC) * 1000.0 > paramTime) {
      
    // }
    attaching = s21_moving(&field, &figure, action);
    if(!attaching) {
      s21_check_and_clear_rows(&field);
      if(s21_check_lose(&field)) {
        s21_game_over(&field, &figure, &nextFigure);
        endwin();
        break;

      } else {
        s21_spawn(&field, &figure, &nextFigure);
      }
      
    }
    usleep(100000);
    for(int i = 0; i < ROWS_FIELD; i++) {
      for(int j = 0; j < COLS_FIELD; j++) {
        printf("%d", field.matrix[i][j]);
      }
      printf("\n");
    }
    printf("\n");

  }

}

void userInput(UserAction_t action, bool hold) {
  condition_t *condition = s21_get_current_condition();
  if(action == Start && condition->status == Init) {
    s21_start_game();
  } else if(action == Pause && condition->status != Init) {

  }else if(action == Terminate && condition->status != Init) {
    s21_clean_condition();
  }else if(action == Left && condition->status == Moving) {
    move_left();
  }else if(action == Right && condition->status == Moving) {
    move_right();
  }else if(action == Down && condition->status == Moving) {
    move_all_down();
  } else if(action == Action && condition->status == Moving) {
    s21_turn();
  }
  s21_move_down();
  condition_t *condition = s21_get_current_condition();
  if(condition->status == Attaching) {
    s21_check_and_clear_rows();
    if(s21_check_lose()) {
      condition->status = GameOver;
    }
  }
}

GameInfo_t updateCurrentState() {
  condition_t *condition = s21_get_current_condition();
  GameInfo_t info = {0};
  info.field = condition->field->matrix;
  info.next = condition->nextFigure->matrix;
  info.score = 0;
  info.high_score = 0;
  info.level = 0;
  info.speed = 0;
  info.pause = 0;
}

void s21_move_left() {
  condition_t *condition = s21_get_current_condition();
  condition->status = Moving;
  s21_remove_figure_on_field();
  s21_move_figure_left();
  s21_add_figure_on_field();
}

void s21_move_right() {
  condition_t *condition = s21_get_current_condition();
  condition->status = Moving;
  s21_remove_figure_on_field();
  s21_move_figure_right();
  s21_add_figure_on_field();
}

void s21_move_all_down() {
  condition_t *condition = s21_get_current_condition();
  condition->status = Attaching;
  s21_remove_figure_on_field();
  s21_move_figure_all_down();
  s21_add_figure_on_field();
}

void s21_move_down() {
  condition_t *condition = s21_get_current_condition();
  if(condition->status != Attaching) {
    condition->status = Moving;
    s21_remove_figure_on_field();
    s21_move_figure_down();
    s21_add_figure_on_field();
  }
  
}

void s21_turn() {
  condition_t *condition = s21_get_current_condition();
  condition->status = Moving;
  s21_remove_figure_on_field();
  s21_turn_figure();
  s21_add_figure_on_field();
}

void s21_init_condition() {
  static condition_t condition = {0};
  s21_create_matrix(ROWS_FIELD, COLS_FIELD, &condition.field->matrix);
  s21_generate_figure(&condition.figure);
  s21_generate_figure(&condition.nextFigure);
  condition.status = Init;
}

void s21_start_game() {
  condition_t *condition = s21_get_current_condition();
  s21_create_matrix(ROWS_FIELD, COLS_FIELD, condition->field->matrix);
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
  condition->status = GameOver;
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



