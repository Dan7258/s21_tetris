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

void s21_init_condition() {
  static condition_t condition = {0};
  s21_create_matrix(ROWS_FIELD, COLS_FIELD, &condition.field->matrix);
  s21_generate_figure(&condition.figure);
  s21_generate_figure(&condition.nextFigure);
  condition.status = Start;
}

condition_t *s21_get_current_condition() {
  static condition_t condition;
  return &condition;
}

void s21_clean_condition(condition_t *condition) {
  s21_remove_matrix(condition->field);
  s21_remove_figure(condition->figure);
  s21_remove_figure(condition->nextFigure);
  condition->status = GameOver;
}

void s21_game_over(matrix_t *field, figure_t *figure, figure_t *nextFigure) {
  s21_remove_matrix(field);
  s21_remove_figure(figure);
  s21_remove_figure(nextFigure);
}

int s21_check_lose(matrix_t *field) {
  int flag = 0;
  for (int m = 0; m < COLS_FIELD && !flag; m++) {
    if(field->matrix[0][m]) {
      flag = 1;
    }
  }
  return flag;
}

void s21_spawn(matrix_t *field, figure_t *figure, figure_t *nextFigure) {
  s21_replace_figure(figure, nextFigure);
  s21_generate_figure(nextFigure);
}

int s21_moving(matrix_t *field, figure_t *figure, UserAction_t action) {
  int flag = 1;
  s21_remove_figure_on_field(field, figure);
  s21_shift(field, figure, action);
  s21_add_figure_on_field(field, figure);
  s21_remove_figure_on_field(field, figure);
  flag = s21_move_figure_down(field, figure);
  s21_add_figure_on_field(field, figure);
  return flag;
}

void s21_shift(matrix_t *field, figure_t *figure, UserAction_t action) {
  switch (action) {
  case Left:
    s21_move_figure_left(field, figure);
    break;
  case Right:
    s21_move_figure_right(field, figure);
    break;
  case Down:
    s21_move_figure_down(field, figure);
    break;
  case Up:
    break;
  }
}

