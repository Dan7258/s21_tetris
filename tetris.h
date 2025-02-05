/**
 * @file tetris.h
 * @brief Заголовочный файл для Tetris.
 */
#ifndef BRICK_GAME_H
#define BRICK_GAME_H

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "brick_game/tetris/api.h"
#include "gui/cli/frontend.h"

/**
 * @brief Получает ввод с клавиатуры.
 * @return Возвращает действие пользователя (например, Up, Down, Action).
 */
UserAction_t getAct();

/**
 * @brief Основной игровой цикл.
 */
void game_loop();

/**
 * @brief Проверяет, завершена ли игра.
 * @details Если в структуре info матрица со следующией фигурой пустая, значит игра завершена.
 * @param info Структура с информацией об игре.
 * @return 1, если игра завершена, иначе 0.
 */
int check_end_game(GameInfo_t info);

/**
 * @brief Очищает память, связанную с текущим состоянием игры.
 * @param info Указатель на структуру с информацией об игре.
 */
void clear_memory(GameInfo_t *info);

/**
 * @brief Возвращает время с момента запуска игры в миллисекундах.
 * @return Количество миллисекунд с момента запуска программы.
 */
unsigned long millis();

#endif
