#include "tetris.h"
#include "brick_game/tetris/backend.h"
#include "gui/cli/frontend.h"

int main() {
  initscr();              
  cbreak();               
  noecho();
  keypad(stdscr, TRUE);
  game_loop();
  getch();
  endwin();
  
  return 0;
}

void game_loop() {
  UserAction_t action;
  UserAction_t preaction;
  GameInfo_t info;
  int flag = 1;
  for(;;) {
    s21_print_start_menu();
    int ch = getch();
    if(ch == KEY_BACKSPACE) {
      flag = 0;
    }
    if(ch == 10) {
      action = Start;
      flag = 1;
    }
    if(ch == 10 || ch == KEY_BACKSPACE) {
      break;
    }

  }
  if(flag) {
    nodelay(stdscr, TRUE); 
    for(;;) {
      userInput(action, true);
      info = updateCurrentState();
      s21_print_owerlay(info);
      if(s21_check_end_game(info)) {
        break;
      }
      preaction = action;
      action = getAct();
      if(action == Pause && preaction != Pause) {
        nodelay(stdscr, FALSE);
      } else {
        nodelay(stdscr, TRUE);
      }
      s21_clear_memory(&info);
    }
    nodelay(stdscr, FALSE); 
    s21_print_game_over_menu(info);
    s21_clear_memory(&info);
  }
  
}

void s21_clear_memory(GameInfo_t *info) {
  for (int m = 0; m < ROWS_FIELD; m++) {
    free(info->field[m]);
  }
  free(info->field);
  info->field = NULL;
  for (int m = 0; m < ROWS_NEXT; m++) {
    free(info->next[m]);
  }
  free(info->next);
  info->next = NULL;
}

UserAction_t getAct() {
  UserAction_t action;
  int ch = getch();
  switch (ch) {
  case 10:
    action = Start;
    break;
  case 27:
    action = Pause;
    break;
  case KEY_UP:
    action = Up;
    break;
  case KEY_LEFT:
    action = Left;
    break;
  case KEY_RIGHT:
    action = Right;
    break;
  case KEY_DOWN:
    action = Down;
    break;
  case 32:
    action = Action;
    break;
  case KEY_BACKSPACE:
    action = Terminate;
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

