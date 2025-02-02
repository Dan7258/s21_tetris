#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>

#include "../../tetris.h"

// frontend functions
void s21_print_owerlay(GameInfo_t gameInfo);
void s21_print_field_frame();
void s21_print_info_frame();
void s21_print_field(GameInfo_t gameInfo);
void s21_print_next_figure(GameInfo_t gameInfo);
void s21_print_score(GameInfo_t gameInfo);
void s21_print_high_score(GameInfo_t gameInfo);
void s21_print_level(GameInfo_t gameInfo);
void s21_print_buttons_frame();
void s21_print_buttons();
void s21_print_start_menu();
void s21_print_pause_menu();
void s21_print_game_over_menu(GameInfo_t gameInfo);

#endif
