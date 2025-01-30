#ifndef FRONTEND_H
#define FRONTEND_H

#include "../../tetris.h"
#include <ncurses.h>

//frontend functions
void s21_print_owerlay(GameInfo_t gameInfo);
void s21_print_frame();
void s21_print_field(GameInfo_t gameInfo);
void s21_print_next_figure(GameInfo_t gameInfo);
void s21_print_score(GameInfo_t gameInfo);
void s21_print_high_score(GameInfo_t gameInfo);
void s21_print_level(GameInfo_t gameInfo);
void s21_print_start_menu();

#endif