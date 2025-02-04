#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>

#include "../../brick_game/tetris/api.h"

// frontend functions
void print_owerlay(GameInfo_t gameInfo);
void print_field_frame();
void print_info_frame();
void print_field(GameInfo_t gameInfo);
void print_next_figure(GameInfo_t gameInfo);
void print_score(GameInfo_t gameInfo);
void print_high_score(GameInfo_t gameInfo);
void print_level(GameInfo_t gameInfo);
void print_buttons_frame();
void print_buttons();
void print_start_menu();
void print_pause_menu();
void print_game_over_menu(GameInfo_t gameInfo);
void clear_field();
#endif
