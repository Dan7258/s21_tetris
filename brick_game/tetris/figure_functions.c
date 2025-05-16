/**
 * @file figure_functions.c
 * @brief Реализация функций для работы с фигурами в игре Тетрис.
 */
#include "backend.h"

void create_figure(SelectedFigure_t SelectedFigure, figure_t *figure) {
  switch (SelectedFigure) {
    case O:
      create_O(figure);
      break;
    case I:
      create_I(figure);
      break;
    case S:
      create_S(figure);
      break;
    case Z:
      create_Z(figure);
      break;
    case L:
      create_L(figure);
      break;
    case J:
      create_J(figure);
      break;
    case T:
      create_T(figure);
      break;
  }
}

void remove_figure(figure_t *figure) {
  if (figure != NULL) {
    remove_matrix(figure->matrix);
  }
}

void generate_figure(figure_t *figure) {
  if (figure != NULL) {
    remove_figure(figure);
    SelectedFigure_t select = rand() % 7;
    create_figure(select, figure);
  }
}

void replace_figure(figure_t *figure, figure_t *nextFigure) {
  remove_figure(figure);
  create_matrix(nextFigure->matrix->rows, nextFigure->matrix->columns,
                figure->matrix);
  copy_matrix(nextFigure->matrix, figure->matrix);
  figure->x = nextFigure->x;
  figure->y = nextFigure->y;
}

void create_O(figure_t *figure) {
  create_matrix(2, 2, figure->matrix);

  figure->matrix->matrix[0][0] = 1;
  figure->matrix->matrix[0][1] = 1;
  figure->matrix->matrix[1][0] = 1;
  figure->matrix->matrix[1][1] = 1;

  figure->x = 4;
  figure->y = -2;
}

void create_I(figure_t *figure) {
  create_matrix(4, 4, figure->matrix);

  figure->matrix->matrix[2][0] = 1;
  figure->matrix->matrix[2][1] = 1;
  figure->matrix->matrix[2][2] = 1;
  figure->matrix->matrix[2][3] = 1;

  figure->x = 3;
  figure->y = -3;
}

void create_S(figure_t *figure) {
  create_matrix(3, 3, figure->matrix);

  figure->matrix->matrix[0][0] = 1;
  figure->matrix->matrix[1][0] = 1;
  figure->matrix->matrix[1][1] = 1;
  figure->matrix->matrix[2][1] = 1;

  figure->x = 4;
  figure->y = -3;
}

void create_Z(figure_t *figure) {
  create_matrix(3, 3, figure->matrix);

  figure->matrix->matrix[0][1] = 1;
  figure->matrix->matrix[1][1] = 1;
  figure->matrix->matrix[1][0] = 1;
  figure->matrix->matrix[2][0] = 1;

  figure->x = 4;
  figure->y = -3;
}

void create_L(figure_t *figure) {
  create_matrix(3, 3, figure->matrix);

  figure->matrix->matrix[0][1] = 1;
  figure->matrix->matrix[1][1] = 1;
  figure->matrix->matrix[2][1] = 1;
  figure->matrix->matrix[2][2] = 1;

  figure->x = 3;
  figure->y = -3;
}

void create_J(figure_t *figure) {
  create_matrix(3, 3, figure->matrix);

  figure->matrix->matrix[0][2] = 1;
  figure->matrix->matrix[1][2] = 1;
  figure->matrix->matrix[2][2] = 1;
  figure->matrix->matrix[2][1] = 1;

  figure->x = 3;
  figure->y = -3;
}

void create_T(figure_t *figure) {
  create_matrix(3, 3, figure->matrix);

  figure->matrix->matrix[1][0] = 1;
  figure->matrix->matrix[1][1] = 1;
  figure->matrix->matrix[1][2] = 1;
  figure->matrix->matrix[2][1] = 1;

  figure->x = 4;
  figure->y = -3;
}

/**
 * @brief Перемещает фигуру влево на один пиксель.
 *
 * Функция проверяет, может ли фигура быть перемещена влево. Если движение
 * возможно, фигура сдвигается на одну ячейку влево. В противном случае,
 * положение фигуры остается неизменным.
 *
 * @details
 * 1. Для каждой ячейки фигуры проверяется, не выходит ли фигура за левую
 * границу поля или не сталкивается ли с другими фигурами на поле.
 * 2. Если хотя бы одна ячейка фигуры не может быть перемещена влево (например,
 * выходит за пределы поля или сталкивается с другой фигурой), флаг `flag`
 * устанавливается в 0, и перемещение не выполняется.
 * 3. Если перемещение возможно, координаты фигуры изменяются, и она сдвигается
 * на одну ячейку влево.
 *
 */

void move_figure_left() {
  int flag = 1;
  condition_t *condition = get_current_condition();
  for (int m = 0; m < condition->figure->matrix->rows && flag; m++) {
    for (int n = 0; n < condition->figure->matrix->columns && flag; n++) {
      if (condition->figure->matrix->matrix[m][n] &&
          n + condition->figure->x - 1 < 0) {
        flag = 0;
      }
      if (n + condition->figure->x - 1 > COLS_FIELD - 1 ||
          m + condition->figure->y < 0) {
        continue;
      } else if (flag && condition->figure->matrix->matrix[m][n] &&
                 condition->field->matrix[m + condition->figure->y]
                                         [n + condition->figure->x - 1]) {
        flag = 0;
      }
    }
  }

  condition->figure->x = flag ? condition->figure->x - 1 : condition->figure->x;
}

/**
 * @brief Перемещает фигуру вправо на один пиксель.
 *
 * Функция проверяет, может ли фигура быть перемещена вправо. Если движение
 * возможно, фигура сдвигается на одну ячейку вправо. В противном случае,
 * положение фигуры остается неизменным.
 *
 * @details
 * 1. Для каждой ячейки фигуры проверяется, не выходит ли фигура за правую
 * границу поля или не сталкивается ли с другими фигурами на поле.
 * 2. Если хотя бы одна ячейка фигуры не может быть перемещена вправо (например,
 * выходит за пределы поля или сталкивается с другой фигурой), флаг `flag`
 * устанавливается в 0, и перемещение не выполняется.
 * 3. Если перемещение возможно, координаты фигуры изменяются, и она сдвигается
 * на одну ячейку вправо.
 *
 */

void move_figure_right() {
  int flag = 1;
  condition_t *condition = get_current_condition();
  for (int m = 0; m < condition->figure->matrix->rows && flag; m++) {
    for (int n = 0; n < condition->figure->matrix->columns && flag; n++) {
      if (condition->figure->matrix->matrix[m][n] &&
          n + condition->figure->x + 1 > COLS_FIELD - 1) {
        flag = 0;
      }
      if (n + condition->figure->x + 1 < 0 || m + condition->figure->y < 0) {
        continue;
      } else if (flag && condition->figure->matrix->matrix[m][n] &&
                 condition->field->matrix[m + condition->figure->y]
                                         [n + condition->figure->x + 1]) {
        flag = 0;
      }
    }
  }

  condition->figure->x = flag ? condition->figure->x + 1 : condition->figure->x;
}

/**
 * @brief Перемещает фигуру вниз на один пиксель.
 *
 * Функция проверяет, может ли фигура быть перемещена вниз. Если движение
 * возможно, фигура сдвигается на одну ячейку вниз. В противном случае, фигура
 * остается на месте.
 *
 * @details
 * 1. Для каждой ячейки фигуры проверяется, не выходит ли фигура за нижнюю
 * границу поля или не сталкивается ли с другими фигурами на поле.
 * 2. Если хотя бы одна ячейка фигуры не может быть перемещена вниз (например,
 * выходит за пределы поля или сталкивается с другой фигурой), флаг `flag`
 * устанавливается в 0, и перемещение не выполняется.
 * 3. Если перемещение возможно, координаты фигуры изменяются, и она сдвигается
 * на одну ячейку вниз.
 *
 * @return Возвращает 1, если перемещение прошло успешно, и 0, если перемещение
 * невозможно (например, из-за столкновения с другой фигурой или выхода за
 * пределы поля).
 */

int move_figure_down() {
  int flag = 1;
  condition_t *condition = get_current_condition();
  for (int m = 0; m < condition->figure->matrix->rows && flag; m++) {
    for (int n = 0; n < condition->figure->matrix->columns && flag; n++) {
      if (condition->figure->matrix->matrix[m][n] &&
          m + condition->figure->y + 1 > ROWS_FIELD - 1) {
        flag = 0;
      }
      if (m + condition->figure->y + 1 < 0) {
        continue;
      } else if (flag && condition->figure->matrix->matrix[m][n] &&
                 condition->field->matrix[m + condition->figure->y + 1]
                                         [n + condition->figure->x]) {
        flag = 0;
      }
    }
  }

  condition->figure->y = flag ? condition->figure->y + 1 : condition->figure->y;
  return flag;
}

void move_figure_all_down() {
  for (; move_figure_down();) {
  }
}

void turn_figure() {
  condition_t *condition = get_current_condition();
  turn_left_matrix(condition->figure->matrix);
  if (!is_figure_valid(condition->figure)) {
    fix_figure(condition->figure);
  }
}

/**
 * @brief Добавляет текущую фигуру на игровое поле.
 *
 * Функция проверяет каждую ячейку текущей фигуры и, если она активна,
 * то добавляет ее в соответствующую позицию на игровом поле. Для этого
 * проверяется, чтобы координаты ячейки фигуры не выходили за пределы игрового
 * поля.
 *
 * @details
 * 1. Функция перебирает все строки и столбцы матрицы фигуры.
 * 2. Для каждой активной ячейки фигуры (где значение матрицы больше нуля)
 * выполняются следующие действия:
 *    - Проверяется, находится ли ячейка внутри границ поля.
 *    - Если ячейка внутри поля, то ее значение (1) записывается в
 * соответствующую ячейку матрицы поля с учетом текущих координат фигуры.
 * 3. Таким образом, фигура фиксируется в текущем положении на игровом поле.
 */
void add_figure_on_field() {
  condition_t *condition = get_current_condition();
  for (int m = 0; m < condition->figure->matrix->rows; m++) {
    for (int n = 0; n < condition->figure->matrix->columns; n++) {
      if (m + condition->figure->y >= 0 &&
          m + condition->figure->y < ROWS_FIELD &&
          condition->figure->matrix->matrix[m][n]) {
        condition->field
            ->matrix[m + condition->figure->y][n + condition->figure->x] = 1;
      }
    }
  }
}

/**
 * @brief Удаляет текущую фигуру с игрового поля.
 *
 * Функция удаляет текущую фигуру с игрового поля, устанавливая соответствующие
 * ячейки поля в значение 0. Для каждой активной ячейки фигуры проверяется,
 * находится ли она внутри границ поля, и если да, то она удаляется.
 *
 * @details
 * 1. Функция перебирает все строки и столбцы матрицы фигуры.
 * 2. Для каждой активной ячейки фигуры (где значение матрицы больше нуля)
 * выполняются следующие действия:
 *    - Проверяется, находится ли ячейка внутри границ игрового поля.
 *    - Если ячейка внутри поля, то значение этой ячейки на игровом поле
 * устанавливается в 0, что удаляет фигуру.
 * 3. Таким образом, фигура удаляется с поля, и ячейки, которые она занимала,
 * становятся пустыми.
 */

void remove_figure_on_field() {
  condition_t *condition = get_current_condition();
  for (int m = 0; m < condition->figure->matrix->rows; m++) {
    for (int n = 0; n < condition->figure->matrix->columns; n++) {
      if (m + condition->figure->y >= 0 &&
          m + condition->figure->y < ROWS_FIELD &&
          condition->figure->matrix->matrix[m][n]) {
        condition->field
            ->matrix[m + condition->figure->y][n + condition->figure->x] = 0;
      }
    }
  }
}

void spawn() {
  condition_t *condition = get_current_condition();
  replace_figure(condition->figure, condition->nextFigure);
  generate_figure(condition->nextFigure);
  condition->status = MovingG;
}

/**
 * @brief Проверяет, является ли текущая фигура допустимой в своем положении на
 * поле.
 *
 * Функция проверяет, может ли текущая фигура быть размещена на игровом поле,
 * учитывая границы поля и возможные столкновения с уже размещенными фигурами.
 *
 * @details
 * 1. Функция перебирает все строки и столбцы матрицы фигуры, начиная с
 * последней строки.
 * 2. Для каждой активной ячейки фигуры выполняются следующие проверки:
 *    - Если строка фигуры выходит за верхнюю границу поля, пропускаем
 * дальнейшие проверки для этой строки.
 *    - Если ячейка фигуры выходит за горизонтальные границы поля (левая или
 * правая граница), возвращаем `false` (недопустимо).
 *    - Если строка фигуры выходит за нижнюю границу поля, возвращаем `false`
 * (недопустимо).
 *    - Если ячейка фигуры перекрывает уже занятые ячейки игрового поля (то есть
 * там уже есть часть другой фигуры), возвращаем `false` (недопустимо).
 * 3. Если все проверки проходят успешно и фигура не выходит за границы поля,
 * возвращаем `true` (фигура допустима).
 *
 * @return Возвращает 1 (истина), если фигура допустима в текущем положении, и 0
 * (ложь), если фигура выходит за границы или сталкивается с другой фигурой.
 */
int is_figure_valid(figure_t *figure) {
  condition_t *condition = get_current_condition();
  int flag = 1;
  for (int m = figure->matrix->rows - 1; m >= 0 && flag; m--) {
    for (int n = 0; n < figure->matrix->columns && flag; n++) {
      if ((m + figure->y < 0)) {
        continue;
      }
      if (figure->matrix->matrix[m][n] &&
          ((n + figure->x) < 0 || (n + figure->x) >= COLS_FIELD)) {
        flag = 0;
      }
      if ((m + figure->y) >= ROWS_FIELD) {
        flag = 0;
      }
      if (flag && condition->field->matrix[m + figure->y][n + figure->x] &&
          figure->matrix->matrix[m][n]) {
        flag = 0;
      }
    }
  }
  return flag;
}

/**
 * @brief Исправляет положение фигуры, чтобы она корректно размещалась на
 * игровом поле.
 *
 * Функция корректирует позицию фигуры в случае, если ее текущие координаты
 * нарушают ограничения игрового поля или если фигура сталкивается с другими уже
 * размещенными фигурами. В случае, если фигура выходит за границы, она будет
 * сдвинута в допустимые координаты.
 *
 * @details
 * 1. Функция сначала сохраняет текущие координаты фигуры для возможного
 * возврата, если фигура не может быть размещена.
 * 2. Для каждой ячейки фигуры выполняются следующие шаги:
 *    - Если фигура выходит за левую границу поля, ее координаты корректируются,
 * сдвигая фигуру вправо.
 *    - Если фигура выходит за правую границу поля, ее координаты
 * корректируются, сдвигая фигуру влево.
 *    - Если фигура сталкивается с другими фигурами, проверяется, можно ли
 * переместить фигуру влево или вправо, пока не будет найдено допустимое место
 * для размещения.
 * 3. После попытки корректировки позиции фигуры проверяется ее валидность. Если
 * фигура невалидна (выходит за границы поля или перекрывает другие фигуры), ее
 * координаты возвращаются к исходным и фигура поворачивается в исходное
 * положение.
 *
 * @param figure Указатель на фигуру, которую необходимо корректировать.
 */

void fix_figure(figure_t *figure) {
  condition_t *condition = get_current_condition();
  int pastX = figure->x;
  int pastY = figure->y;
  for (int m = figure->matrix->rows - 1; m >= 0; m--) {
    for (int n = 0; n < figure->matrix->columns; n++) {
      if (figure->matrix->matrix[m][n] && (n + figure->x) < 0) {
        figure->x += 0 - (n + figure->x);
      } else if (figure->matrix->matrix[m][n] &&
                 (n + figure->x) >= COLS_FIELD) {
        figure->x -= (n + figure->x) - (COLS_FIELD - 1);
      } else if ((m + figure->y) < ROWS_FIELD && figure->matrix->matrix[m][n] &&
                 condition->field->matrix[m + figure->y][n + figure->x] &&
                 n <= figure->matrix->columns / 2) {
        for (; figure->matrix->matrix[m][n] &&
               condition->field->matrix[m + figure->y][n + figure->x];
             figure->x++) {
        }
      } else if ((m + figure->y) < ROWS_FIELD && figure->matrix->matrix[m][n] &&
                 condition->field->matrix[m + figure->y][n + figure->x] &&
                 n > figure->matrix->columns / 2) {
        for (; figure->matrix->matrix[m][n] &&
               condition->field->matrix[m + figure->y][n + figure->x];
             figure->x--) {
        }
      }
    }
  }
  if (!is_figure_valid(figure)) {
    figure->x = pastX;
    figure->y = pastY;
    turn_right_matrix(figure->matrix);
  }
}
