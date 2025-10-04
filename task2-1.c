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
* @brief Структура для хранения трех чисел.
*/
typedef struct {
    double a;
    double b;
    double c;
    int success; // Флаг успешного ввода
} Numbers;

/**
* @brief Функция сортировки трех чисел методом пузырька.
* @param a - Первое число.
* @param b - Второе число.
* @param c - Третье число.
* @param order - Порядок сортировки (increase или descending).
*/
void sortNumbers(double* a, double* b, double* c, SortOrder order);

/**
* @brief Функция считывания выбора порядка сортировки с проверкой ввода.
* @return Возвращает выбранный порядок сортировки, или 0 при ошибке.
*/
SortOrder getSortOrder();

/**
* @brief Функция считывания трех чисел с клавиатуры с проверкой ввода.
* @return Возвращает структуру Numbers с числами и флагом успеха.
*/
Numbers getValues();

/**
* @brief Точка входа в программу.
* @param numbers - Структура для хранения трех введенных чисел и флага успешного ввода
* @details - Функция setlocale(LC_ALL, "") устанавливает локаль по умолчанию системы, что обеспечивает правильное отображение русских символов.
* @return Возвращает 0 если программа выполнена корректно, иначе 1.
*/
int main(void) {
    char* locale = setlocale(LC_ALL, "");

    Numbers numbers = getValues();
    if (!numbers.success) {
        return 1;
    }
    SortOrder order = getSortOrder();
    if (order != increase && order != descending) {
        printf("Ошибка выбора порядка сортировки!\n");
        return 1;
    }

    sortNumbers(&numbers.a, &numbers.b, &numbers.c, order);

    // Выводим результат в зависимости от выбора пользователя.
    if (order == increase) {
        printf("Числа в порядке возрастания: %.2f, %.2f, %.2f\n", numbers.a, numbers.b, numbers.c);
    }
    else {
        printf("Числа в порядке убывания: %.2f, %.2f, %.2f\n", numbers.a, numbers.b, numbers.c);
    }

    return 0;
}

Numbers getValues() {
    Numbers nums;
    nums.success = 0;

    printf("Введите три числа a, b, c: ");
    if (scanf("%lf %lf %lf", &nums.a, &nums.b, &nums.c) == 3) {
        nums.success = 1; // Успешный ввод
    }
    else {
        printf("Ошибка ввода! Требуется три вещественных числа.\n");
    }

    return nums;
}

SortOrder getSortOrder() {
    int choice;
    printf("Выберите порядок сортировки:\n");
    printf("%d - по возрастанию\n", increase);
    printf("%d - по убыванию\n", descending);
    printf("Ваш выбор: ");

    if (scanf("%d", &choice) != 1) {
        printf("Ошибка ввода!\n");
        return 0;
    }

    switch (choice)
    {
    case increase: return increase;
    case descending: return descending;
    default:
        printf("Неверный выбор! Допустимые значения: %d или %d\n", increase, descending);
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
