/**
 * @file fsm.c
 * @brief Реализация функций конечного автомата для игры Тетрис.
 */
#include "backend.h"

/**
 * @brief Обрабатывает ввод пользователя и изменяет состояние игры.
 *
 * @param action Действие пользователя (тип UserAction_t).
 * @param hold Флаг зажатия кнопки (true - удержание, false - одиночное
 * нажатие).
 *
 * @details
 * Алгоритм работы:
 * 1. Получаем текущее состояние игры (`condition`) с помощью
 * `get_current_condition()`.
 * 2. В зависимости от переданного действия `action` выполняем соответствующие
 * операции:
 *    - **Start**: Запуск игры (`start_game()`).
 *    - **Pause**: Если статус игры не `InitG`, переключаем между `PauseG` и
 * `MovingG`.
 *    - **Terminate**:
 *      - Если статус `PauseG`, завершаем игру (`game_over()`).
 *      - Если статус `GameOverG`, очищаем данные (`clean_condition()`).
 *    - **Left**: Если статус `MovingG`, перемещаем фигуру влево
 * (`move_left()`).
 *    - **Right**: Если статус `MovingG`, перемещаем фигуру вправо
 * (`move_right()`).
 *    - **Down**:
 *      - Если `hold == false`, опускаем фигуру до упора (`move_all_down()`).
 *      - Если `hold == true`, опускаем фигуру на один шаг (`move_down()`).
 *    - **Action**: Если статус `MovingG`, выполняем поворот фигуры (`turn()`).
 * 3. Если состояние игры `AttachingG` (фигура достигла дна):
 *    - Проверяем и очищаем заполненные ряды (`check_and_clear_rows()`).
 *    - Обновляем очки (`check_score(count)`) и уровень (`check_level()`).
 *    - Проверяем, не наступило ли поражение (`check_lose()`):
 *      - Если поражение не наступило, создаём новую фигуру (`spawn()`).
 *      - Если игра проиграна, вызываем `game_over()`.
 */
void userInput(UserAction_t action, bool hold) {
  condition_t *condition = get_current_condition();
  if (action == Start) {
    start_game();
  } else if (action == Pause && condition->status != InitG) {
    condition->status = condition->status == PauseG ? MovingG : PauseG;
  } else if (action == Terminate && condition->status == PauseG) {
    game_over();
  } else if (action == Terminate && condition->status == GameOverG) {
    clean_condition();
  } else if (action == Left && condition->status == MovingG) {
    move_left();
  } else if (action == Right && condition->status == MovingG) {
    move_right();
  } else if (action == Down && condition->status == MovingG && !hold) {
    move_all_down();
  } else if (action == Down && condition->status == MovingG && hold) {
    move_down();
  } else if (action == Action && condition->status == MovingG) {
    turn();
  }
  if (condition->status == AttachingG) {
    int count = check_and_clear_rows();
    check_score(count);
    check_level();
    if (!check_lose()) {
      spawn();
    } else {
      game_over();
    }
  }
}

GameInfo_t updateCurrentState() {
  condition_t *condition = get_current_condition();
  GameInfo_t info = {0};
  info.field = (int **)malloc(ROWS_FIELD * sizeof(int *));
  for (int i = 0; i < ROWS_FIELD; i++) {
    info.field[i] = (int *)calloc(COLS_FIELD, sizeof(int));
  }
  for (int m = 0; m < ROWS_FIELD; m++) {
    for (int n = 0; n < COLS_FIELD; n++) {
      info.field[m][n] = condition->field->matrix[m][n];
    }
  }

  info.next = (int **)malloc(ROWS_NEXT * sizeof(int *));
  for (int i = 0; i < ROWS_NEXT; i++) {
    info.next[i] = (int *)calloc(COLS_NEXT, sizeof(int));
  }
  for (int m = 0; m < condition->nextFigure->matrix->rows; m++) {
    for (int n = 0; n < condition->nextFigure->matrix->columns; n++) {
      info.next[m][n] = condition->nextFigure->matrix->matrix[m][n];
    }
  }
  info.score = condition->score;
  info.high_score = condition->high_score;
  info.level = condition->level;
  info.speed = condition->level + 1;
  info.pause = condition->status == PauseG ? 1 : 0;
  return info;
}

/**
 * @brief Проверяет и очищает полностью заполненные ряды в игровом поле.
 *
 * @return Количество удалённых рядов.
 *
 * @details
 * Алгоритм работы:
 * 1. Получаем текущее состояние игры (`condition`) через
 * `get_current_condition()`.
 * 2. Инициализируем счётчик `counter` для подсчёта удалённых рядов.
 * 3. Начинаем проверку строк снизу вверх (`m` от `ROWS_FIELD - 1` до `0`):
 *    - Если строка `m` полностью заполнена (`check_filled_row(m)`):
 *      - Увеличиваем `counter`.
 *      - Смещаем все вышерасположенные строки вниз:
 *        - Проходим по строкам от `m` до `1`.
 *        - Копируем содержимое строки `f-1` в строку `f`.
 *      - Обнуляем верхнюю строку (`matrix[0][n] = 0`).
 *      - Увеличиваем `m`, чтобы повторно проверить текущую строку после сдвига.
 * 4. Возвращаем количество удалённых строк `counter`.
 */
int check_and_clear_rows() {
  condition_t *condition = get_current_condition();
  int counter = 0;
  for (int m = ROWS_FIELD - 1; m >= 0; m--) {
    if (check_filled_row(m)) {
      counter++;
      for (int f = m; f > 0; f--) {
        for (int n = 0; n < COLS_FIELD; n++) {
          condition->field->matrix[f][n] = condition->field->matrix[f - 1][n];
        }
      }
      for (int n = 0; n < COLS_FIELD; n++) {
        condition->field->matrix[0][n] = 0;
      }
      m++;
    }
  }
  return counter;
}

void check_score(int count) {
  condition_t *condition = get_current_condition();
  switch (count) {
    case 1:
      condition->score += 100;
      break;
    case 2:
      condition->score += 300;
      break;
    case 3:
      condition->score += 700;
      break;
    case 4:
      condition->score += 1500;
      break;
  }
  if (condition->score > condition->high_score) {
    condition->high_score = condition->score;
  }
}

void check_level() {
  condition_t *condition = get_current_condition();
  if (condition->score / 600 + 1 > 10) {
    condition->level = 10;
  } else {
    condition->level = condition->score / 600 + 1;
  }
}

int check_filled_row(int m) {
  condition_t *condition = get_current_condition();
  int flag = 1;
  for (int n = 0; n < COLS_FIELD && flag; n++) {
    flag = (condition->field->matrix[m][n]) ? flag : 0;
  }
  return flag;
}

void move_left() {
  condition_t *condition = get_current_condition();
  condition->status = MovingG;
  remove_figure_on_field();
  move_figure_left();
  add_figure_on_field();
}

void move_right() {
  condition_t *condition = get_current_condition();
  condition->status = MovingG;
  remove_figure_on_field();
  move_figure_right();
  add_figure_on_field();
}

void move_all_down() {
  condition_t *condition = get_current_condition();
  condition->status = AttachingG;
  remove_figure_on_field();
  move_figure_all_down();
  add_figure_on_field();
}

void move_down() {
  condition_t *condition = get_current_condition();
  if (condition->status != AttachingG) {
    condition->status = MovingG;
    remove_figure_on_field();
    if (!move_figure_down()) {
      condition->status = AttachingG;
    }
    add_figure_on_field();
  }
}

void turn() {
  condition_t *condition = get_current_condition();
  condition->status = MovingG;
  remove_figure_on_field();
  turn_figure();
  add_figure_on_field();
}

void init_condition() {
  condition_t *condition = get_current_condition();
  condition->field = malloc(sizeof(matrix_t));
  condition->figure = malloc(sizeof(figure_t));
  condition->nextFigure = malloc(sizeof(figure_t));
  condition->figure->matrix = malloc(sizeof(matrix_t));
  condition->nextFigure->matrix = malloc(sizeof(matrix_t));
  create_matrix(ROWS_FIELD, COLS_FIELD, condition->field);
  generate_figure(condition->figure);
  generate_figure(condition->nextFigure);
  condition->status = InitG;
  check_level();
  condition->high_score = get_high_score_from_file();
}

void start_game() {
  condition_t *condition = get_current_condition();
  if (condition->status == PauseG || condition->status == GameOverG) {
    remove_matrix(condition->field);
    condition->status = InitG;
    condition->score = 0;
    check_level();
    set_high_score_in_file(condition->high_score);
  }
  if (condition->field == NULL) {
    init_condition();
  }
  if (condition->status == InitG) {
    create_matrix(ROWS_FIELD, COLS_FIELD, condition->field);
    generate_figure(condition->figure);
    generate_figure(condition->nextFigure);
    condition->status = MovingG;
  }
}

condition_t *get_current_condition() {
  static condition_t condition;
  return &condition;
}

void clean_condition() {
  condition_t *condition = get_current_condition();
  set_high_score_in_file(condition->high_score);
  remove_matrix(condition->field);
  remove_figure(condition->figure);
  remove_figure(condition->nextFigure);
}

void game_over() {
  condition_t *condition = get_current_condition();
  remove_matrix(condition->nextFigure->matrix);
  create_matrix(5, 5, condition->nextFigure->matrix);
  for (int i = 0; i < ROWS_NEXT; i++) {
    for (int j = 0; j < COLS_NEXT; j++) {
      condition->nextFigure->matrix->matrix[i][j] = 0;
    }
  }
  condition->status = GameOverG;
  set_high_score_in_file(condition->high_score);
}

int check_lose() {
  condition_t *condition = get_current_condition();
  int flag = 0;
  for (int m = 0; m < COLS_FIELD && !flag; m++) {
    if (condition->field->matrix[0][m] == 1) {
      flag = 1;
    }
  }
  return flag;
}

int get_high_score_from_file() {
  int high_score = 0;
  FILE *file;
  file = fopen("data.txt", "r");
  if (file) {
    fscanf(file, "%d", &high_score);
    fclose(file);
  }
  return high_score;
}

void set_high_score_in_file(int high_score) {
  FILE *file;
  file = fopen("data.txt", "w");
  fprintf(file, "%d", high_score);
  fclose(file);
}
