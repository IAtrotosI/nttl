#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

/**
* @brief Вычисление значения функции y = 2(cos²x - 1)
* @param x - Аргумент функции
* @return double - Значение функции в точке x
*/
double vichislit_y(const double x);

/**
* @brief Вычисление суммы функционального ряда для функции 2(cos²x - 1)
* @param x - Аргумент, для которого вычисляется ряд
* @param epsilon - Точность вычисления суммы ряда
* @return double - Сумма ряда с заданной точностью
*/
double vichislit_ryad(const double x, const double epsilon);

/**
* @brief Табулирование функции и её ряда на заданном интервале
* @param start - Начальная точка интервала
* @param end - Конечная точка интервала
* @param step - Шаг табулирования
* @param epsilon - Точность вычисления ряда
*/
void tabulirovat(const double start, const double end, const double step, const double epsilon);

/**
* @brief Точка входа в программу
* @return Возвращает 0 если программа выполненна верно
*/
int main(void)
{
    setlocale(LC_ALL, "");

    const double A = 0.1;      // Начало интервала
    const double B = 1.0;      // Конец интервала
    const double H = 0.1;      // Шаг табулирования
    const double EPS = 1.0 / pow(15, 4);  // Точность 15^(-4)

    printf("Вариант 12\n");
    printf("Функция: y = 2(cos²x - 1)\n");
    printf("Ряд: S = -(2x)²/2 + (2x)⁴/24 - (2x)⁶/720 + ... + (-1)ⁿ(2x)²ⁿ/(2n)!\n");
    printf("Интервал: [%.1f, %.1f], шаг: %.1f, точность: %.2e\n", A, B, H, EPS);
    printf("==============================================================\n\n");

    tabulirovat(A, B, H, EPS);

    return 0;
}

double vichislit_y(const double x)
{
    return cos(2.0 * x) - 1.0;
}

double vichislit_ryad(const double x, const double epsilon)
{
    const double two_x = 2.0 * x;  // 2x
    double two_x_power = two_x * two_x;  // (2x)^2
    double factorial = 2.0;        // 2! для первого члена
    double sum = 0.0;
    int n = 1;
    const int MAX_ITERATIONS = 50;

    for (int k = 1; k <= MAX_ITERATIONS; k++)
    {
        // Вычисляем k-й член ряда: (-1)^k * (2x)^(2k) / (2k)!
        double term = ((k % 2 == 1) ? -1.0 : 1.0) * two_x_power / factorial;

        sum += term;

        // Проверка достижения точности
        if (fabs(term) < epsilon)
        {
            return sum;
        }

        // Подготовка следующего члена ряда
        two_x_power *= two_x * two_x;

        // Увеличиваем факториал: (2k)! -> (2k+2)!
        factorial *= (2 * k + 1) * (2 * k + 2);

        n++;
    }

    return sum;
}

void tabulirovat(const double start, const double end, const double step, const double epsilon)
{
    printf("%-10s %-15s %-15s\n", "x", "y", "Сумма ряда");
    printf("----------------------------------------\n");

    for (double x = start; x <= end + DBL_EPSILON; x += step)
    {
        double y = vichislit_y(x);
        double sum_ryada = vichislit_ryad(x, epsilon);

        printf("%-10.4f %-15.8f %-15.8f\n", x, y, sum_ryada);
    }
}
