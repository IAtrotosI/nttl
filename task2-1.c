#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

/**
* @brief Перечислимый тип для выбора порядка сортировки.
*/
typedef enum
{
    increase = 1,   // Сортировка по возрастанию.
    descending = 2   // Сортировка по убыванию.
} SortOrder;

/**
* @brief Функция сортировки трех чисел методом пузырька.
* @param a - Первое число.
* @param b - Второе число.
* @param c - Третье число.
* @param order - Порядок сортировки (increase или descending).
* @param temp - Кешированная переменная.
* @details - Функция ничего не возвращает, т.к работает с переменными через указатели.
*/
void sortNumbers(double* a, double* b, double* c, SortOrder order);

/**
* @brief Функция считывания выбора порядка сортировки с проверкой ввода.
* @param choice - Порядок сортировки.
* @return Возвращает выбранный порядок сортировки, 1 при успешном вводе, или 0 при ошибке.
*/
SortOrder getSortOrder();

/**
* @brief Функция считывания трех чисел с клавиатуры с проверкой ввода.
* @param a - Указатель на первое число.
* @param b - Указатель на второе число.
* @param c - Указатель на третье число.
* @return Возвращает 1 при успешном вводе, 0 при ошибке.
*/
int getValues(double* a, double* b, double* c);

/**
* @brief Точка входа в программу.
* @param a - Первое число.
* @param b - Второе число.
* @param c - Третье число.
* @param order - Порядок сортировки (increase или descending).
* @details - Функция setlocale(LC_ALL, "") устанавливает локаль по умолчанию системы, что обеспечивает правильное отображение русских символов.
* @return Возвращает 0 если программа выполнена корректно, иначе 1.
*/
int main(void) {
    char* locale = setlocale(LC_ALL, "");
    double a, b, c;

    // Считываем значения.
    if (!getValues(&a, &b, &c)) {
        return 1; // Завершаем программу при ошибке ввода.
    }
    // Считываем выбор порядка сортировки.
    SortOrder order = getSortOrder();
    if (order != increase && order != descending) {
        printf("Ошибка выбора порядка сортировки!\n");
        return 1;
    }

    sortNumbers(&a, &b, &c, order); // Сортируем числа в выбранном порядке.

    // Выводим результат в зависимости от выбора пользователя.
    if (order == increase) {
        printf("Числа в порядке возрастания: %.2f, %.2f, %.2f\n", a, b, c);
    }
    else {
        printf("Числа в порядке убывания: %.2f, %.2f, %.2f\n", a, b, c);
    }

    return 0;
}

int getValues(double* a, double* b, double* c) {
    printf("Введите три числа a, b, c: ");
    if (scanf("%lf %lf %lf", a, b, c) != 3) {
        printf("Ошибка ввода! Требуется три вещественных числа.\n");
        return 0; // Возвращаем 0 при ошибке.
    }
    return 1; // Возвращаем 1 при успехе.
}

SortOrder getSortOrder() {
    int choice;
    printf("Выберите порядок сортировки:\n");
    printf("1 - по возрастанию\n");
    printf("2 - по убыванию\n");
    printf("Ваш выбор: ");

    if (scanf("%d", &choice) != 1) {
        printf("Ошибка ввода!\n");
        return 0;
    }

    if (choice == 1) {
        return increase;
    }
    else if (choice == 2) {
        return descending;
    }
    else {
        printf("Неверный выбор! Допустимые значения: 1 или 2\n");
        return 0;
    }
}

void sortNumbers(double* a, double* b, double* c, SortOrder order) {
    double temp;
    // Сортировка методом пузырька для трех чисел
    if ((order == increase && *a > *b) || (order == descending && *a < *b)) {
        temp = *a;
        *a = *b;
        *b = temp;
    }
    if ((order == increase && *b > *c) || (order == descending && *b < *c)) {
        temp = *b;
        *b = *c;
        *c = temp;
    }
    if ((order == increase && *a > *b) || (order == descending && *a < *b)) {
        temp = *a;
        *a = *b;
        *b = temp;
    }
}
