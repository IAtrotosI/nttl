#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

/**
* @brief Функция вычисления значения y.
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
* @brief Функция табулирования функции и ряда на заданном интервале.
* @param start - Начало интервала.
* @param end - Конец интервала.
* @param step - Шаг табулирования.
* @param epsilon - Точность вычисления ряда.
*/
void tabulirovat(const double start, const double end, const double step, const double epsilon);

/**
* @brief Точка входа в программу.
* @param A = 0.1    - начальная точка интервала табулирования
* @param B = 0.8    - конечная точка интервала табулирования  
* @param H = 0.01   - шаг изменения аргумента x
* @param EPS = 40^(-5) - точность вычисления суммы функционального ряда
* @return 0 - Программа выполнена корректно.
*/
int main(void)
{
    setlocale(LC_ALL, "");

    const double A = 0.1;
    const double B = 0.8;
    const double H = 0.01;
    const double EPS = 1.0 / pow(40, 5);

    printf("Вариант 13\n");
    printf("Функция: y = ln(1/(2 + 2x + x²))\n");
    printf("Ряд: S = -(1+x)² + (1+x)⁴/2 - (1+x)⁶/3 + ...\n");
    printf("Интервал: [%.1f, %.1f], шаг: %.2f, точность: %.0e\n", A, B, H, EPS);
    printf("============================================\n\n");

    tabulirovat(A, B, H, EPS);

    return 0;
}

double vichislit_y(const double x)
{
    double denominator = 2.0 + 2.0 * x + x * x;

    if (denominator <= DBL_EPSILON) return NAN;

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

void tabulirovat(const double start, const double end, const double step, const double epsilon)
{
    printf("%-10s %-15s %-15s\n", "x", "y", "Сумма ряда");
    printf("----------------------------------------\n");

    for (double x = start; x <= end + DBL_EPSILON; x += step)
    {
        double y = vichislit_y(x);
        double sum_ryada = vichislit_ryad(x, epsilon);

        if (!isnan(y) && !isnan(sum_ryada))
        {
            printf("%-10.4f %-15.8f %-15.8f\n", x, y, sum_ryada);
        }
        else
        {
            printf("%-10.4f %-15s %-15s\n", x,
                isnan(y) ? "N/A" : "OK",
                isnan(sum_ryada) ? "N/A" : "OK");
        }
    }
}
