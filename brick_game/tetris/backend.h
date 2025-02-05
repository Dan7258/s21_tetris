/**
 * @file backend.h
 * @brief Заголовочный файл для backend-функций игры Тетрис.
 */

#ifndef BACKEND_H
#define BACKEND_H

#include <stdio.h>
#include <stdlib.h>

#include "api.h"

/**
 * @brief Структура, представляющая матрицу.
 */
typedef struct matrix {
  int **matrix; /**< Двумерный массив, представляющий содержимое матрицы */
  int rows;     /**< Количество строк в матрице */
  int columns;  /**< Количество столбцов в матрице */
} matrix_t;

/**
 * @brief Структура, представляющая фигуру в игре.
 */
typedef struct figure {
  matrix_t *matrix; /**< Матрица, определяющая форму фигуры */
  int x; /**< Координата X (горизонтальное положение) */
  int y; /**< Координата Y (вертикальное положение) */
} figure_t;

/**
 * @brief Перечисление возможных фигур в игре.
 */
typedef enum { O = 0, I, S, Z, L, J, T } SelectedFigure_t;

/**
 * @brief Перечисление возможных состояний игры.
 */
typedef enum {
  InitG,      /**< Начальное состояние игры */
  StartG,     /**< Игра запущена */
  PauseG,     /**< Игра на паузе */
  MovingG,    /**< Фигура в движении */
  AttachingG, /**< Фигура достигла дна или фигуры */
  GameOverG   /**< Игра окончена */
} GameStatus_t;

/**
 * @brief Структура, содержащая текущее состояние игры.
 */
typedef struct condition {
  matrix_t *field;      /**< Игровое поле */
  figure_t *figure;     /**< Текущая падающая фигура */
  figure_t *nextFigure; /**< Следующая фигура */
  GameStatus_t status;  /**< Текущий статус игры */
  int score;            /**< Текущий счет игрока */
  int high_score;       /**< Рекордный счет */
  int level;            /**< Текущий уровень */
} condition_t;

// ======= Функции для работы с матрицами =======

/**
 * @brief Создает матрицу заданного размера.
 * @param rows Количество строк.
 * @param columns Количество столбцов.
 * @param result Указатель на структуру, в которой будет создана матрица.
 */
void create_matrix(int rows, int columns, matrix_t *result);

/**
 * @brief Удаляет матрицу, освобождая память.
 * @param M Указатель на матрицу для удаления.
 */
void remove_matrix(matrix_t *M);

/**
 * @brief Поворачивает матрицу влево на 90 градусов.
 * @param M Указатель на матрицу для поворота.
 */
void turn_left_matrix(matrix_t *M);

/**
 * @brief Поворачивает матрицу вправо на 90 градусов.
 * @param M Указатель на матрицу для поворота.
 */
void turn_right_matrix(matrix_t *M);

/**
 * @brief Копирует содержимое одной матрицы в другую.
 * @param M Исходная матрица.
 * @param result Указатель на матрицу, в которую будет произведено копирование.
 */
void copy_matrix(matrix_t *M, matrix_t *result);

// ======= Функции для работы с фигурами =======

/**
 * @brief Создает фигуру заданного типа.
 * @param SelectedFigure Тип создаваемой фигуры.
 * @param figure Указатель на структуру фигуры.
 */
void create_figure(SelectedFigure_t SelectedFigure, figure_t *figure);

/**
 * @brief Удаляет фигуру, освобождая память.
 * @param figure Указатель на удаляемую фигуру.
 */
void remove_figure(figure_t *figure);

/**
 * @brief Генерирует случайную фигуру.
 * @param figure Указатель на создаваемую фигуру.
 */
void generate_figure(figure_t *figure);

/**
 * @brief Заменяет текущую фигуру на следующую.
 * @param figure Текущая фигура.
 * @param nextFigure Следующая фигура.
 */
void replace_figure(figure_t *figure, figure_t *nextFigure);

/**
 * @brief Создает фигуру "O".
 * @param figure Указатель на создаваемую фигуру.
 */
void create_O(figure_t *figure);

/**
 * @brief Создает фигуру "I".
 * @param figure Указатель на создаваемую фигуру.
 */
void create_I(figure_t *figure);

/**
 * @brief Создает фигуру "S".
 * @param figure Указатель на создаваемую фигуру.
 */
void create_S(figure_t *figure);

/**
 * @brief Создает фигуру "Z".
 * @param figure Указатель на создаваемую фигуру.
 */
void create_Z(figure_t *figure);

/**
 * @brief Создает фигуру "L".
 * @param figure Указатель на создаваемую фигуру.
 */
void create_L(figure_t *figure);

/**
 * @brief Создает фигуру "J".
 * @param figure Указатель на создаваемую фигуру.
 */
void create_J(figure_t *figure);

/**
 * @brief Создает фигуру "T".
 * @param figure Указатель на создаваемую фигуру.
 */
void create_T(figure_t *figure);

/**
 * @brief Перемещает фигуру влево на один пиксель.
 */
void move_figure_left();

/**
 * @brief Перемещает фигуру вправо на один пиксель.
 */
void move_figure_right();

/**
 * @brief Перемещает фигуру вниз на один пиксель.
 * @return 1, если фигура смогла опуститься, 0 - если достигла дна.
 */
int move_figure_down();

/**
 * @brief Опускает фигуру вниз до упора.
 */
void move_figure_all_down();

/**
 * @brief Поворачивает фигуру.
 */
void turn_figure();

/**
 * @brief Добавляет фигуру на игровое поле.
 */
void add_figure_on_field();

/**
 * @brief Удаляет фигуру с игрового поля.
 */
void remove_figure_on_field();

/**
 * @brief Обновляет текущую фигуру и генерирует следующую.
 */
void spawn();

/**
 * @brief Проверяет, является ли текущая фигура допустимой в своем положении на
 * поле.
 * @param figure Указатель на фигуру.
 * @return 1 - можно, 0 - нельзя.
 */
int is_figure_valid(figure_t *figure);

/**
 * @brief Исправляет положение фигуры, чтобы она корректно размещалась на
 * игровом поле.
 * @param figure Указатель на фигуру.
 */
void fix_figure(figure_t *figure);

// ======= Функции конечного автомата (FSM) =======

/**
 * @brief Проверяет и удаляет заполненные ряды.
 * @return Количество удаленных рядов.
 */
int check_and_clear_rows();

/**
 * @brief Проверяет, заполнена ли строка.
 * @param m Индекс строки.
 * @return 1 - если заполнена, 0 - если нет.
 */
int check_filled_row(int m);

/**
 * @brief Обновляет очки игрока.
 * @param count Количество удаленных рядов.
 */
void check_score(int count);

/**
 * @brief Проверяет и обновляет уровень игрока.
 */
void check_level();

/**
 * @brief Перемещает фигуру влево.
 */
void move_left();

/**
 * @brief Перемещает фигуру вправо.
 */
void move_right();

/**
 * @brief Опускает фигуру вниз до упора.
 */
void move_all_down();

/**
 * @brief Опускает фигуру на один шаг вниз.
 */
void move_down();

/**
 * @brief Поворачивает текущую фигуру.
 */
void turn();

/**
 * @brief Инициализация игрового состояния.
 *
 * Выделяет память для игрового поля и фигур, создает игровое поле и генерирует
 * первые фигуры. Устанавливает начальное состояние игры и загружает рекордный
 * счет из файла.
 */
void init_condition();

/**
 * @brief Запуск игры.
 *
 * Если игра была в состоянии паузы или завершения, то очищает игровое поле,
 * сбрасывает очки и обновляет уровень. Если поле не было инициализировано,
 * вызывает `init_condition()`. После инициализации игра переходит в состояние
 * движения фигур.
 */
void start_game();

/**
 * @brief Получение текущего состояния игры.
 *
 * @return Указатель на структуру `condition_t`, содержащую текущее состояние
 * игры.
 */
condition_t *get_current_condition();

/**
 * @brief Очистка состояния игры.
 *
 * Освобождает память, выделенную для игрового поля и фигур.
 * Сохраняет рекордный счет перед завершением.
 */
void clean_condition();

/**
 * @brief Завершение игры.
 *
 * Очищает данные следующей фигуры и создает пустую матрицу для нее.
 * Устанавливает состояние игры в `GameOverG` и сохраняет рекордный счет.
 */
void game_over();

/**
 * @brief Проверяет, наступило ли поражение.
 * @return 1 - если проигрыш, 0 - если можно продолжать игру.
 */
int check_lose();

/**
 * @brief Получает рекордный счет из файла.
 * @return Рекордный счет.
 */
int get_high_score_from_file();

/**
 * @brief Записывает рекордный счет в файл.
 * @param high_score Новый рекорд.
 */
void set_high_score_in_file(int high_score);
#endif
