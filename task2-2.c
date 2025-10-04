#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>

/**
* @brief Функция вычисления значения y по заданной формуле.
* @param a - Параметр a.
* @param x - Аргумент x.
* @param y - Аргумент y.
* @return Возвращает вычисленное значение y.
*/
double naiti_y(double a, double x);

/**
* @brief Функция считывания аргумента x с клавиатуры с проверкой ввода.
* @param x - Аргумент x.
* @return Возвращает x при успешном вводе, завершает выполнение программы при ошибке.
*/
double argument_x(void);


/**
* @brief Точка входа в программу.
* @param a - Параметр a.
* @param x - Аргумент x.
* @param y - Аргумент y.
* @details - Функция setlocale(LC_ALL, "") устанавливает локаль по умолчанию системы, что обеспечивает правильное отображение русских символов.
* @return Возвращает 0 если программа выполнена корректно, иначе 1.
*/
int main(void) 
{
    char* locale = setlocale(LC_ALL, "");
    const double a = 2.5;
    
    printf("Программа вычисления функции y = f(x)\n");
    printf("Параметр a = %.1f\n", a);

    double x = argument_x();
    double y = naiti_y(a, x);

    printf("\nРезультаты вычислений:\n");
    printf("a = %.1f\n", a);
    printf("x = %.2f\n", x);
    printf("y = %.4f\n", y);

    return 0;
}

double argument_x(void)
{
    double x = 0;
    printf("Введите значение x: ");
    if (scanf("%lf", &x) != 1)
    {
        printf("Ошибка ввода! Требуется вещественное число.\n");
        exit(1);
    }
    return x;
}

double naiti_y(const double a, double x) 
{
    double y = 0;
    if (x > 0.5)
    {
        y = sqrt(a * a * x - 1);
        printf("При: x > 0.5, y = sqrt(%.1f^2*x - 1)\n", a);
    }
    else if (x < 0.5) 
    {
        y = sqrt((a * x * x) + 1);
        printf("При: x < 0.5, y = sqrt(%.1f*x^2 + 1)\n", a);
    }
    else 
    {
        y = a * x + 3;
        printf("При: x = 0.5, y = %.1f*x + 3\n", a);
    }

    return y;
}
