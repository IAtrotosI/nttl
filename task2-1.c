#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>

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
* @param minv - Минимальное из чисел.
* @param midv - Среднее из чисел.
* @param maxv - Максимальное из чисел.
*/
void sort_and_print_Numbers(const double a, const double b, const double c, SortOrder order);

/**
* @brief Функция считывания трех чисел с клавиатуры с проверкой ввода.
* @return Возвращает структуру Numbers с числами и флагом успеха.
*/
int getValue();

/**
* @brief Точка входа в программу.
* @param numbers - Структура для хранения трех введенных чисел и флага успешного ввода
* @details - Функция setlocale(LC_ALL, "") устанавливает локаль по умолчанию системы, что обеспечивает правильное отображение русских символов.
* @return Возвращает 0 если программа выполнена корректно, иначе 1.
*/
int main(void) {
    char* locale = setlocale(LC_ALL, "");
    int a = getValue();
    int b = getValue();
    int c = getValue();
    printf("Выберите порядок сортировки:\n");
    printf("%d - по возрастанию\n", increase);
    printf("%d - по убыванию\n", descending);
    printf("Ваш выбор: ");
    int choice = getValue();
    sort_and_print_Numbers(a, b, c, choice);
    return 0;
}

int getValue(void) 
{
    int num = 0;

    printf("Введите число: ");
    if (!scanf("%d", &num)) 
    {
        printf("Ошибка ввода!\n");
        exit(1);
    }

    return num;
}


void sort_and_print_Numbers(double a, double b, double c, int order)
{
    double minv = min(a, min(b, c));
    double maxv = max(a, max(b, c));
    double midv = (a + b + c) - minv - maxv;

    switch (order)
    {
    case increase:
        printf("Числа в порядке возрастания: %.2f, %.2f, %.2f\n", minv, midv, maxv);
        break;
    case descending:
        printf("Числа в порядке убывания: %.2f, %.2f, %.2f\n", maxv, midv, minv);
        break;
    default:
        printf("Неправильный выбор\n");
    }
}
