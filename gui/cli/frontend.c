/**
 * @file frontend.c
 * @brief Отображение интерфейса игры Тетрис
 *
 * @details Этот файл содержит реализацию функций для отрисовки различных
 * элементов игрового интерфейса.
 */

#include "frontend.h"

void handle_resize() { endwin(); }

void print_owerlay(GameInfo_t gameInfo) {
  signal(SIGWINCH, handle_resize);
  print_field(gameInfo);
  print_next_figure(gameInfo);
  print_high_score(gameInfo);
  print_score(gameInfo);
  print_level(gameInfo);
  print_field_frame();
  print_info_frame();
  print_buttons_frame();
  print_buttons();
  mvaddch(0, COLS_FIELD * 2 + 13, ' ');
  refresh();
}

void print_start_menu() {
  signal(SIGWINCH, handle_resize);
  mvaddstr(2, 8, "TETRIS");
  mvaddstr(4, 2, "Press \"Enter\" to");
  mvaddstr(5, 2, "start the game");
  mvaddstr(7, 2, "OR");
  mvaddstr(9, 2, "Press \"Terminate\"");
  mvaddstr(10, 2, "to exit the game");
  print_field_frame();
  print_info_frame();
  print_buttons_frame();
  print_buttons();
  mvaddch(0, COLS_FIELD * 2 + 13, ' ');
  refresh();
}

void print_pause_menu() {
  signal(SIGWINCH, handle_resize);
  clear_field();
  mvaddstr(2, 8, "PAUSE");
  mvaddstr(4, 2, "Press \"p\" to");
  mvaddstr(5, 2, "continue the game");
  mvaddstr(7, 2, "OR");
  mvaddstr(9, 2, "Press \"Terminate\"");
  mvaddstr(10, 2, "to exit the game");
  mvaddstr(12, 2, "OR");
  mvaddstr(14, 2, "Press \"Enter\"");
  mvaddstr(15, 2, "to restart the game");
  print_field_frame();
  print_info_frame();
  print_buttons_frame();
  print_buttons();
  mvaddch(0, COLS_FIELD * 2 + 13, ' ');
  refresh();
}

void clear_field() {
  for (int i = 0; i < ROWS_FIELD; i++) {
    for (int j = 0; j < COLS_FIELD; j++) {
      mvaddch(i + 1, j * 2 + 1, ' ');
      mvaddch(i + 1, j * 2 + 2, ' ');
    }
  }
}

void print_game_over_menu(GameInfo_t gameInfo) {
  signal(SIGWINCH, handle_resize);
  clear_field();
  mvaddstr(2, 7, "GAME OVER");
  mvprintw(4, 2, "Your score: %d", gameInfo.score);
  mvaddstr(9, 2, "Press \"Terminate\"");
  mvaddstr(10, 2, "to exit the game");
  mvaddstr(12, 2, "OR");
  mvaddstr(14, 2, "Press \"Enter\"");
  mvaddstr(15, 2, "to restart the game");
  print_field_frame();
  print_info_frame();
  print_buttons_frame();
  print_buttons();
  mvaddch(0, COLS_FIELD * 2 + 13, ' ');
  refresh();
}

void print_field_frame() {
  mvaddch(0, 0, ACS_ULCORNER);
  mvaddch(0, COLS_FIELD * 2 + 1, ACS_URCORNER);
  mvaddch(ROWS_FIELD + 1, 0, ACS_LLCORNER);
  mvaddch(ROWS_FIELD + 1, COLS_FIELD * 2 + 1, ACS_LRCORNER);

  for (int i = 0; i < ROWS_FIELD + 2; i += ROWS_FIELD + 1) {
    for (int j = 1; j < COLS_FIELD * 2 + 1; j++) {
      mvaddch(i, j, ACS_HLINE);
    }
  }

  for (int i = 1; i < ROWS_FIELD + 1; i++) {
    for (int j = 0; j < COLS_FIELD * 2 + 2; j += COLS_FIELD * 2 + 1) {
      mvaddch(i, j, ACS_VLINE);
    }
  }
}

void print_info_frame() {
  mvaddch(0, COLS_FIELD * 2 + 2, ACS_ULCORNER);
  mvaddch(0, COLS_FIELD * 2 + 12, ACS_URCORNER);
  mvaddch(ROWS_FIELD + 1, COLS_FIELD * 2 + 2, ACS_LLCORNER);
  mvaddch(ROWS_FIELD + 1, COLS_FIELD * 2 + 12, ACS_LRCORNER);

  for (int i = 0; i < ROWS_FIELD + 2; i += ROWS_FIELD + 1) {
    for (int j = COLS_FIELD * 2 + 3; j < COLS_FIELD * 2 + 12; j++) {
      mvaddch(i, j, ACS_HLINE);
    }
  }

  for (int i = 1; i < ROWS_FIELD + 1; i++) {
    for (int j = COLS_FIELD * 2 + 2; j < COLS_FIELD * 2 + 13; j += 10) {
      mvaddch(i, j, ACS_VLINE);
    }
  }
}

void print_field(GameInfo_t gameInfo) {
  for (int i = 0; i < ROWS_FIELD; i++) {
    for (int j = 0; j < COLS_FIELD; j++) {
      if (gameInfo.field[i][j]) {
        mvaddch(i + 1, j * 2 + 1, ACS_CKBOARD);
        mvaddch(i + 1, j * 2 + 2, ACS_CKBOARD);
      } else {
        mvaddch(i + 1, j * 2 + 1, ' ');
        mvaddch(i + 1, j * 2 + 2, ' ');
      }
    }
  }
}

void print_high_score(GameInfo_t gameInfo) {
  char buffer[20];
  mvaddstr(2, COLS_FIELD * 2 + 3, "record:");
  sprintf(buffer, "%d", gameInfo.high_score);
  mvaddstr(3, COLS_FIELD * 2 + 4, "       ");
  mvaddstr(3, COLS_FIELD * 2 + 4, buffer);
}

void print_score(GameInfo_t gameInfo) {
  char buffer[20];
  mvaddstr(5, COLS_FIELD * 2 + 3, "score:");
  sprintf(buffer, "%d", gameInfo.score);
  mvaddstr(6, COLS_FIELD * 2 + 4, "       ");
  mvaddstr(6, COLS_FIELD * 2 + 4, buffer);
}

void print_level(GameInfo_t gameInfo) {
  char buffer[20];
  mvaddstr(8, COLS_FIELD * 2 + 3, "level:");
  sprintf(buffer, "%d", gameInfo.level);
  mvaddstr(9, COLS_FIELD * 2 + 3, "      ");
  mvaddstr(9, COLS_FIELD * 2 + 4, buffer);
}

void print_next_figure(GameInfo_t gameInfo) {
  mvaddstr(11, COLS_FIELD * 2 + 3, "next:");

  for (int i = 0; i < ROWS_NEXT; i++) {
    for (int j = 0; j < COLS_NEXT; j++) {
      if (gameInfo.next[i][j]) {
        mvaddch(i + 12, (j * 2) + COLS_FIELD * 2 + 4, ACS_CKBOARD);
        mvaddch(i + 12, (j * 2) + COLS_FIELD * 2 + 5, ACS_CKBOARD);
      } else {
        mvaddch(i + 12, (j * 2) + COLS_FIELD * 2 + 4, ' ');
        mvaddch(i + 12, (j * 2) + COLS_FIELD * 2 + 5, ' ');
      }
    }
  }
}

void print_buttons_frame() {
  mvaddch(ROWS_FIELD + 2, 0, ACS_ULCORNER);
  mvaddch(ROWS_FIELD + 2, COLS_FIELD * 2 + 12, ACS_URCORNER);
  mvaddch(ROWS_FIELD + 8, 0, ACS_LLCORNER);
  mvaddch(ROWS_FIELD + 8, COLS_FIELD * 2 + 12, ACS_LRCORNER);

  for (int i = ROWS_FIELD + 2; i < ROWS_FIELD + 9; i += 6) {
    for (int j = 1; j < COLS_FIELD * 2 + 12; j++) {
      mvaddch(i, j, ACS_HLINE);
    }
  }

  for (int i = ROWS_FIELD + 3; i < ROWS_FIELD + 8; i++) {
    for (int j = 0; j < COLS_FIELD * 2 + 13; j += COLS_FIELD * 2 + 12) {
      mvaddch(i, j, ACS_VLINE);
    }
  }
}

void print_buttons() {
  mvaddstr(ROWS_FIELD + 3, 1, "^ - not used");
  mvaddstr(ROWS_FIELD + 4, 1, "-> - move right");
  mvaddstr(ROWS_FIELD + 5, 1, "<- - move left");
  mvaddstr(ROWS_FIELD + 6, 1, "v - move down");
  mvaddstr(ROWS_FIELD + 7, 1, "space - turn");

  for (int j = ROWS_FIELD + 3; j < ROWS_FIELD + 8; j++) {
    mvaddch(j, 16, ACS_VLINE);
  }

  mvaddstr(ROWS_FIELD + 3, 17, "p - pause");
  mvaddstr(ROWS_FIELD + 4, 17, "enter - start");
  mvaddstr(ROWS_FIELD + 5, 17, "backspace");
  mvaddstr(ROWS_FIELD + 6, 21, "- terminate");
}
