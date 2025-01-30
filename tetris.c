#include "tetris.h"
#include "brick_game/tetris/backend.h"
#include "gui/cli/frontend.h"

int main() {
  initscr();              
  cbreak();               
  noecho();
  game_loop();
  getch();
  endwin();
  
  return 0;
}

void game_loop() {
  s21_print_start_menu();
  UserAction_t action = getAct();
  nodelay(stdscr, TRUE); 
  GameInfo_t info;
  info = updateCurrentState();
  for(;!s21_check_end_game(info);) {
    userInput(action, true);
    s21_clear_memory(&info);
    info = updateCurrentState();
    s21_print_owerlay(info);
    action = getAct();
  }
  nodelay(stdscr, FALSE); 
  
  s21_print_owerlay(info);
  s21_clear_memory(&info);
}

void s21_clear_memory(GameInfo_t *info) {
  for (int m = 0; m < ROWS_NEXT; m++) {
    free(info->next[m]);
  }
  free(info->next);
  info->next = NULL;
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

int s21_check_end_game(GameInfo_t info) {
  int flag = 1;
  for(int i = 0; i < ROWS_NEXT; i++) {
    for(int j = 0; j < COLS_NEXT; j++) {
      if(info.next[i][j]) {
        flag = 0;
      }
    }
  }
  return flag;
}

