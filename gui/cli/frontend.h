/**
 * @file frontend.h
 * @brief Заголовочный файл для функций фронтенда игры Тетрис.
 *
 * @details Этот файл содержит объявления функций, используемых для отображения
 * интерфейса игры Тетрис с использованием библиотеки ncurses.
 */
#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>
#include <signal.h>

#include "../../brick_game/tetris/api.h"

/**
 * @brief Проверяет изменение размера терминала
 */
void handle_resize();

/**
 * @brief Отображает основной интерфейс игры
 * @param gameInfo Структура с информацией об игре.
 */
void print_owerlay(GameInfo_t gameInfo);

/**
 * @brief Отрисовывает рамку игрового поля.
 */
void print_field_frame();

/**
 * @brief Отрисовывает рамку для дополнительной информации в игре.
 */
void print_info_frame();

/**
 * @brief Отрисовывает игровое поле с текущим состоянием игры.
 *
 * @param gameInfo Структура с информацией об игре.
 */
void print_field(GameInfo_t gameInfo);

/**
 * @brief Отрисовывает следующую фигуру, которая появится в игре.
 *
 * @param gameInfo Структура с информацией об игре.
 */
void print_next_figure(GameInfo_t gameInfo);

/**
 * @brief Отрисовывает текущий счет игры.
 *
 * @param gameInfo Структура с информацией об игре.
 */
void print_score(GameInfo_t gameInfo);

/**
 * @brief Отрисовывает рекордный счет игры.
 *
 * @param gameInfo Структура с информацией об игре.
 */
void print_high_score(GameInfo_t gameInfo);

/**
 * @brief Отрисовывает текущий уровень игры.
 *
 * @param gameInfo Структура с информацией об игре.
 */
void print_level(GameInfo_t gameInfo);

/**
 * @brief Отрисовывает рамку для кнопок управления.
 */
void print_buttons_frame();

/**
 * @brief Отрисовывает кнопки управления.
 */
void print_buttons();

/**
 * @brief Отрисовывает стартовое меню игры.
 */
void print_start_menu();

/**
 * @brief Отрисовывает меню паузы игры.
 */
void print_pause_menu();

/**
 * @brief Отрисовывает меню окончания игры с итоговой информацией об игре.
 *
 * @param gameInfo Структура с информацией об игре.
 */
void print_game_over_menu(GameInfo_t gameInfo);

/**
 * @brief Очищает игровое поле.
 */
void clear_field();

#endif
