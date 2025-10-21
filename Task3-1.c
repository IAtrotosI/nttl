#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>

/**
* @brief Функция ввода числа с проверкой.
* @param message - Сообщение для пользователя.
* @param chislo - Введенное пользователем число
* @return chislo - Введенное пользователем число.
*/
double getValue(void);

/**
* @brief Функция вычисления значения y = 3*ln^2(x) + 6*ln(x) - 5.
* @param x - Аргумент x, для которого вычисляется функция.
* @param ln_x - Значение натурального логарифма от x.
* @return y - Вычисленное значение функции.
* @return NAN - Если x <= 0 и ln(x) не существует.
*/
double vichislit_y(const double x);

/**
* @brief Точка входа в программу.
* @return start - Начало интервала табулирования.
* @return end - Конец интервала табулирования.
* @return delta_x - Шаг табулирования.
* @param x - Аргумент x, для которого вычисляется функция.
* @return y - Вычисленное значение функции.
* @return 0 - Программа выполнена корректно.
*/
int main(void)
{
    char* locale = setlocale(LC_ALL, "");

    printf("Программа табулирования функции y = 3*ln^2(x) + 6*ln(x) - 5\n");
    printf("======================================================\n");

    printf("Введите начало интервала (x начальное): ");
    double start = getValue();
    printf("Введите конец интервала (x конечное): ");
    double end = getValue();
    printf("Введите шаг табулирования: ");
    double delta_x = getValue();

    printf("\nРезультаты табулирования:\n");
    printf("==========================\n");
    printf("%-10s %-15s %-15s\n", "x", "y", "Статус");
    printf("----------------------------------------\n");

    double x = start;
    double y = 0;

    for (x = start; x <= end + 1e-9; x += delta_x)
    {
        y = vichislit_y(x);

        if (!isnan(y))
        {
            printf("%-10.4f %-15.4f %-15s\n", x, y, "Успех");
        }
        else
        {
            printf("%-10.4f %-15s %-15s\n", x, "N/A", "Ошибка: ln(x) не существует");
        }
    }

    return 0;
}

double getValue(void)
{
    double chislo = 0;
    if (scanf("%lf", &chislo) != 1)
    {
        printf("Ошибка ввода! Требуется вещественное число.\n");
        exit(1);
    }

    return chislo;
}

double vichislit_y(const double x)
{
    if (x <= 0)
    {
        return NAN;
    }

    double ln_x = log(x);
    double y = 3 * ln_x * ln_x + 6 * ln_x - 5;
    return y;
}
