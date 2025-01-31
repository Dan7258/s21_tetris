#include "frontend.h"

void s21_print_owerlay(GameInfo_t gameInfo) {
  s21_print_field_frame();
  s21_print_field(gameInfo);
  s21_print_info_frame();
  s21_print_next_figure(gameInfo);
  s21_print_high_score(gameInfo);
  s21_print_score(gameInfo);
  s21_print_level(gameInfo);
  s21_print_buttons_frame();
  s21_print_buttons();
  mvaddch(0, COLS_FIELD * 2 + 13, ' ');
  refresh();
}

void s21_print_start_menu() {
  mvprintw(5, 5, "press enter");
  refresh();
}

void s21_print_field_frame() {
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

void s21_print_info_frame() {
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

void s21_print_field(GameInfo_t gameInfo) {
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

void s21_print_high_score(GameInfo_t gameInfo) {
  char score[] = "record:";
  for (int i = 0; i < 7; i++) {
    mvaddch(2, i + COLS_FIELD * 2 + 3, score[i]);
  }

  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%d", gameInfo.high_score);
  for (int i = 0; buffer[i] != '\0'; i++) {
    mvaddch(3, i + COLS_FIELD * 2 + 4, buffer[i]);
  }
}

void s21_print_score(GameInfo_t gameInfo) {
  char score[] = "score:";
  for (int i = 0; i < 6; i++) {
    mvaddch(5, i + COLS_FIELD * 2 + 3, score[i]);
  }

  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%d", gameInfo.score);
  for (int i = 0; buffer[i] != '\0'; i++) {
    mvaddch(6, i + COLS_FIELD * 2 + 4, buffer[i]);
  }
}

void s21_print_level(GameInfo_t gameInfo) {
  char score[] = "level:";
  for (int i = 0; i < 6; i++) {
    mvaddch(12, i + COLS_FIELD * 2 + 3, score[i]);
  }

  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%d", gameInfo.level);
  for (int i = 0; buffer[i] != '\0'; i++) {
    mvaddch(13, i + COLS_FIELD * 2 + 4, buffer[i]);
  }
}

void s21_print_next_figure(GameInfo_t gameInfo) {
  char score[] = "next:";
  for (int i = 0; i < 5; i++) {
    mvaddch(8, i + COLS_FIELD * 2 + 3, score[i]);
  }

  for (int i = 0; i < ROWS_NEXT; i++) {
    for (int j = 0; j < COLS_NEXT; j++) {
      if (gameInfo.next[i][j]) {
        mvaddch(i + 9, j + COLS_FIELD * 2 + 4, ACS_BLOCK);
      } else {
        mvaddch(i + 9, j + COLS_FIELD * 2 + 4, ' ');
      }
    }
  }
}

void s21_print_buttons_frame() {
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

void s21_print_buttons(){
  mvaddstr(ROWS_FIELD + 3, 1, "^ - not used");
  mvaddstr(ROWS_FIELD + 4, 1, "-> - move right");
  mvaddstr(ROWS_FIELD + 5, 1, "<- - move left");
  mvaddstr(ROWS_FIELD + 6, 1, "v - move down");
  mvaddstr(ROWS_FIELD + 7, 1, "space - turn");

  for (int j = ROWS_FIELD + 3; j < ROWS_FIELD + 8; j ++) {
    mvaddch(j, 16, ACS_VLINE);
  }

  mvaddstr(ROWS_FIELD + 3, 17, "esc - pause");
  mvaddstr(ROWS_FIELD + 4, 17, "enter - start");
  mvaddstr(ROWS_FIELD + 5, 17, "backspace");
  mvaddstr(ROWS_FIELD + 6, 21, "- terminate");
}
