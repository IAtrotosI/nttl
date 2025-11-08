#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

/**
 * @brief Считывает целое значение с клавиатуры с проверкой ввода
 * @return Возвращает считанное значение
 */
int getIntValue();

/**
 * @brief Считывает вещественное значение с клавиатуры с проверкой ввода
 * @return Возвращает считанное значение
 */
double getDoubleValue();

/**
 * @brief Вычисляет сумму первых n членов последовательности
 * @param n Количество членов последовательности
 * @return Вычисленная сумма
 */
double calculateSumN(const int n);

/**
 * @brief Вычисляет сумму членов последовательности, по модулю не меньших заданного числа e
 * @param e Заданная точность (минимальный модуль члена)
 * @return Вычисленная сумма
 */
double calculateSumE(const double e);

/**
 * @brief Вычисляет рекуррентный коэффициент для перехода от k-го к (k+1)-му члену
 * @param k Текущий индекс
 * @return Рекуррентный коэффициент
 */
double getRecurrent(const int k);

/**
 * @brief Проверяет, что число положительное
 * @param value Проверяемое значение
 */
void checkPositive(const double value);

int main(void)
{
    char* locale = setlocale(LC_ALL, "");
    printf("Программа для вычисления суммы последовательности\n");

    // Часть a: сумма первых n членов
    printf("Часть a: Сумма первых n членов\n");
    printf("Введите n: ");
    int n = getIntValue();
    checkPositive((double)n);

    double sumN = calculateSumN(n);
    printf("Сумма первых %d членов последовательности: %.6lf\n\n", n, sumN);

    // Часть b: сумма членов с модулем >= e
    printf("Часть b: Сумма членов с модулем >= e\n");
    printf("Введите e: ");
    double e = getDoubleValue();
    checkPositive(e);

    double sumE = calculateSumE(e);
    printf("Сумма членов последовательности с модулем >= %.6lf: %.6lf\n", e, sumE);

    return 0;
}

int getIntValue(void)
{
    int value = 0;
    if (scanf("%d", &value) != 1)
    {
        printf("Ошибка ввода! Требуется целое число.\n");
        exit(1);
    }
    return value;
}

double getDoubleValue(void)
{
    double value = 0;
    if (scanf("%lf", &value) != 1)
    {
        printf("Ошибка ввода! Требуется вещественное число.\n");
        exit(1);
    }
    return value;
}

void checkPositive(const double value)
{
    if (value <= 0)
    {
        printf("Ошибка! Число должно быть положительным.\n");
        exit(1);
    }
}

double getRecurrent(const int k)
{
    return -1.0 / ((2 * k + 2) * (2 * k + 1));
}

double calculateSumN(const int n)
{
    if (n <= 0) return 0;

    double current = 1.0; // a_0 = (-1)^0 / (0)! = 1/1 = 1
    double sum = current;

    for (int k = 0; k < n - 1; k++)
    {
        current *= getRecurrent(k);
        sum += current;
    }

    return sum;
}

double calculateSumE(const double e)
{
    double current = 1.0;
    double sum = current;
    int k = 0;

    while (fabs(current) >= e)
    {
        current *= getRecurrent(k);
        if (fabs(current) >= e)
        {
            sum += current;
        }
        k++;
    }

    return sum;
}
