#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

#define A 0.1
#define B 0.8  
#define H 0.01
#define EPS 1e-5

/**
* @brief Функция вычисления значения y = ln(1/(2 + 2x + x²)).
* @param x - Аргумент x, для которого вычисляется функция.
* @return y - Вычисленное значение функции.
* @return NAN - Если выражение под логарифмом <= 0.
*/
double vichislit_y(const double x);

/**
* @brief Функция вычисления суммы функционального ряда для данной функции.
* @param x - Аргумент x, для которого вычисляется ряд.
* @param epsilon - Точность вычисления ряда.
* @return sum - Сумма ряда с заданной точностью.
*/
double vichislit_ryad(const double x, const double epsilon);

/**
* @brief Точка входа в программу.
* @return 0 - Программа выполнена корректно.
*/
int main(void)
{
    setlocale(LC_ALL, "");

    printf("Вариант 13\n");
    printf("Интервал: [%.1f, %.1f], шаг: %.1f, точность: %.0e\n", A, B, H, EPS);
    printf("============================================\n\n");

    printf("%-10s %-15s %-15s\n", "x", "y", "Сумма ряда");
    printf("-------------------------------------------\n");

    for (double x = A; x <= B + DBL_EPSILON; x += H)
    {
        double y = vichislit_y(x);
        double sum_ryada = vichislit_ryad(x, EPS);

        if (!isnan(y) && !isnan(sum_ryada))
        {
            printf("%-10.4f %-15.8f %-15.8f\n", x, y, sum_ryada);
        }
        else
        {
            printf("%-10.4f %-15.8f %-15s %-15s\n", x, y,
                isnan(sum_ryada) ? "РАСХОДИТСЯ" : "OK", "N/A");
        }
    }

    return 0;
}

double vichislit_y(const double x)
{
    double denominator = 2.0 + 2.0 * x + x * x;

    if (denominator <= DBL_EPSILON)
        return NAN;

    return -log(denominator);
}

double vichislit_ryad(const double x, const double epsilon)
{
    double u = 1.0 / ((1.0 + x) * (1.0 + x));
    double sum = -2.0 * log(1.0 + x);
    double term = u;
    int n = 1;

    do
    {
        double current_term = ((n % 2 == 1) ? -1.0 : 1.0) * term / n;
        double old_sum = sum;
        sum += current_term;

        if (fabs(current_term) < epsilon)
        {
            break;
        }

        term *= u;
        n++;

        if (n > 1000)
        {
            return NAN;
        }

    } while (1);

    return sum;
}
