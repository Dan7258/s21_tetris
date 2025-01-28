#include "brick_game.h"

void s21_print_owerlay(GameInfo_t gameInfo) {
    s21_print_frame();
    s21_print_field(gameInfo);
    // s21_print_next_figure(gameInfo);
    s21_print_high_score(gameInfo);
    s21_print_score(gameInfo);
    s21_print_level(gameInfo);
    
    refresh();
}

void s21_print_start_menu() {
    mvprintw(5, 5, "press enter"); // Функция mvprintw перемещает курсор и печатает строку
    refresh();  
}

void s21_print_frame() {
    mvaddch(0, 0, ACS_ULCORNER);
    mvaddch(0, COLS_FIELD + 1, ACS_URCORNER);
    mvaddch(ROWS_FIELD + 1, 0, ACS_LLCORNER);
    mvaddch(ROWS_FIELD + 1, COLS_FIELD + 1, ACS_LRCORNER);

    for(int i = 0; i < ROWS_FIELD + 2; i += ROWS_FIELD + 1) {
        for(int j = 1; j < COLS_FIELD + 1; j++) {
            mvaddch(i, j, ACS_HLINE);
        }
    }

    for(int i = 1; i < ROWS_FIELD + 1; i++) {
        for(int j = 0; j < COLS_FIELD + 2; j+= COLS_FIELD + 1) {
            mvaddch(i, j, ACS_VLINE);
        }
    }
}

void s21_print_field(GameInfo_t gameInfo) {
    for(int i = 0; i < ROWS_FIELD; i++) {
        for(int j = 0; j < COLS_FIELD ; j++) {
            if(gameInfo.field[i][j]) {
                mvaddch(i + 1, j + 1, ACS_CKBOARD);
            } else {
                mvaddch(i + 1, j + 1, ' ');
            }
            
        }
    }
}

void s21_print_high_score(GameInfo_t gameInfo) {
    char score[] = "record:";
    for(int i = 0; i < 7; i++) {
        mvaddch(2, i + COLS_FIELD + 2, score[i]);    
    }

    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%d", gameInfo.high_score);
    for (int i = 0; buffer[i] != '\0'; i++) {
        mvaddch(3, i + COLS_FIELD + 4, buffer[i]);
    }
}

void s21_print_score(GameInfo_t gameInfo) {
    char score[] = "score:";
    for(int i = 0; i < 6; i++) {
        mvaddch(5, i + COLS_FIELD + 2, score[i]);    
    }

    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%d", gameInfo.score);
    for (int i = 0; buffer[i] != '\0'; i++) {
        mvaddch(6, i + COLS_FIELD + 4, buffer[i]);
    }
}

void s21_print_level(GameInfo_t gameInfo) {
    char score[] = "level:";
    for(int i = 0; i < 6; i++) {
        mvaddch(8, i + COLS_FIELD + 2, score[i]);    
    }

    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%d", gameInfo.level);
    for (int i = 0; buffer[i] != '\0'; i++) {
        mvaddch(9, i + COLS_FIELD + 4, buffer[i]);
    }
}

void s21_print_next_figure(GameInfo_t gameInfo) {
    for(int i = 0; i < sizeof(gameInfo.next) / sizeof(int); i++) {
        for(int j = 0; j < sizeof(gameInfo.next[i]) / sizeof(int); j++) {
            if(gameInfo.next[i][j]) {
                mvaddch(i + 1, j + 1, ACS_BLOCK);
            } else {
                mvaddch(i + 1, j + 1, ' ');
            }
        }
    }
}