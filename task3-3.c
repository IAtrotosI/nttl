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

    double A = 0, B = 0, H = 0, EPS = 0;

    printf("Введите начало интервала A: ");
    scanf("%lf", &A);

    printf("Введите конец интервала B: ");
    scanf("%lf", &B);

    printf("Введите шаг табулирования H: ");
    scanf("%lf", &H);

    printf("Введите точность EPS (например, 0.000019): ");
    scanf("%lf", &EPS);

    printf("\nИнтервал: [%.3f, %.3f], шаг: %.3f, точность: %.2e\n", A, B, H, EPS);
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
    const double two_x = 2.0 * x;
    const double two_x_squared = two_x * two_x;
    double term = -two_x_squared / 2.0;     // Первый член при n=1
    double sum = term;
    double denominator = 2.0;               //Текущий знаменатель
    int n = 1;
    const int MAX_ITERATIONS = 100;

    if (fabs(term) < epsilon)
        return sum;

    for (int k = 2; k <= MAX_ITERATIONS; k++)
    {
        n++;

        term *= (-1.0) * two_x_squared / ((2 * n - 1) * (2 * n));

        sum += term;

        if (fabs(term) < epsilon)
        {
            return sum;
        }
    }

    return sum;
}

void tabulirovat(const double start, const double end, const double step, const double epsilon)
{
    printf("%-12s %-18s %-18s\n", "x", "y", "Сумма ряда");
    printf("------------------------------------------------\n");

    for (double x = start; x <= end + DBL_EPSILON; x += step)
    {
        double y = vichislit_y(x);
        double sum_ryada = vichislit_ryad(x, epsilon);

        printf("%-12.6f %-18.10f %-18.10f\n", x, y, sum_ryada);
    }
}
