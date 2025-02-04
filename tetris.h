#ifndef BRICK_GAME_H
#define BRICK_GAME_H

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "brick_game/tetris/api.h"
#include "gui/cli/frontend.h"

// game funtions
UserAction_t getAct();
void game_loop();
int check_end_game(GameInfo_t info);
void clear_memory(GameInfo_t *info);
unsigned long millis();

#endif
