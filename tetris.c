/**
 * @file tetris.c
 * @brief Реализация игры Тетрис в виде конечного автомата.
 */
#include "tetris.h"

/**
 * @brief Точка входа в программу.
 * @return Код завершения программы.
 */
int main() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  srand(time(NULL));
  game_loop();
  nodelay(stdscr, FALSE);
  endwin();

  return 0;
}

/**
 * @brief Основной игровой цикл.
 *
 * Функция `game_loop` управляет игровым процессом, обрабатывая ввод
 * пользователя, обновляя состояние игры и отображая интерфейс. Также она
 * обрабатывает паузу и завершение игры.
 *
 * @details
 * 1. Отображается стартовое меню.
 * 2. Ожидается начало игры (`Start`) или завершение (`Terminate`).
 * 3. Запускается основной цикл игры:
 *    - Обрабатывается ввод пользователя.
 *    - Обновляется состояние игры.
 *    - Раз в (1000 / speed) мс вызывается автоматическое обновление для
 * смещения фигуры вниз на 1 линию.
 *    - Отображается текущее состояние игры.
 *    - Если активирована пауза, ожидается её отключение или рестарта игры или
 * выхода в главное меню.
 *    - Если игра окончена, отображается меню завершения и ожидается новая игра
 * или выход.
 * 4. При выходе из игры освобождается память.
 */

void game_loop() {
  UserAction_t action = Up;
  UserAction_t preaction = Terminate;
  GameInfo_t info;
  unsigned long time = millis();
  bool hold = false;
  print_start_menu();
  for (; action != Start && action != Terminate; action = getAct()) {
  }
  for (;;) {
    userInput(action, hold);
    hold = false;
    if (preaction == Terminate && action == Terminate) {
      break;
    }
    info = updateCurrentState();
    if (millis() - time > 1000.0 / info.speed) {
      clear_memory(&info);
      action = Down;
      hold = true;
      time = millis();
      continue;
    }
    print_owerlay(info);
    if (info.pause) {
      print_pause_menu();
      clear_memory(&info);
      action = Up;
      for (; action != Start && action != Terminate && action != Pause;
           action = getAct()) {
      }
      preaction = Up;
    } else if (check_end_game(info)) {
      print_game_over_menu(info);
      clear_memory(&info);
      action = Up;
      for (; action != Start && action != Terminate; action = getAct()) {
      }
      preaction = action;
    } else {
      preaction = Up;
      action = getAct();
      clear_memory(&info);
    }
  }
}

void clear_memory(GameInfo_t *info) {
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
    case 112:
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
  }
  return action;
}

int check_end_game(GameInfo_t info) {
  int flag = 1;
  for (int i = 0; i < ROWS_NEXT; i++) {
    for (int j = 0; j < COLS_NEXT; j++) {
      if (info.next[i][j]) {
        flag = 0;
      }
    }
  }
  return flag;
}

unsigned long millis() {
  return (unsigned long)(clock() * 1000 / CLOCKS_PER_SEC);
}
