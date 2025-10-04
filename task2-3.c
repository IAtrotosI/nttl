#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>

/**
* @brief Функция проверки корректности ввода числа x.
* @param x - Аргумент x. Данные введённые пользователем.
* @return Возвращает введенное значение x при успешном вводе.
*/
double proverka_x(void);

/**
* @brief Функция вычисления и сортировки значений функций.
* @param x - Аргумент x.
* @param ln_x - Аргуент содержащий значение вычисления ln(x).
* @param has_ln - Аргумент подтверждающий/отрицающий существование ln_x.
* @details - Вычисляет sin(x), cos(x), ln(x) и выводит их в порядке возрастания.
*/
void vichislenie_i_sortirovka(const double x);

/**
* @brief Точка входа в программу.
* @details - Функция setlocale(LC_ALL, "") устанавливает локаль по умолчанию системы.
* @return Возвращает 0 если программа выполнена корректно.
*/
int main(void)
{
    char* locale = setlocale(LC_ALL, "");

    printf("Программа вычисления и сортировки значений: sin(x), cos(x), ln(x)\n");
    printf("=================================================================\n");

    double x = proverka_x();
    vichislenie_i_sortirovka(x);

    return 0;
}

double proverka_x(void)
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

void vichislenie_i_sortirovka(const double x)
{
    double ln_x = 0;
    int has_ln = 1;

    printf("\nВведенное значение x = %.4f\n", x);
    printf("========================================\n");

    // Проверка существования ln(x)
    if (x > 0)
    {
        ln_x = log(x);
    }
    else
    {
        has_ln = 0;
        printf("Внимание: ln(x) не существует при x <= 0!\n");
    }

    printf("\nЗначения в порядке возрастания:\n");
    printf("========================================\n");

    // Сортировка и вывод в порядке возрастания
    if (has_ln)
    {
        // Все три функции существуют - сортируем прямо в условиях
        /* Как по мне с функцией обмена, которая была в прошлом коммите на много проще и быстрее, код короче и понятнее */
        if (sin(x) <= cos(x) && sin(x) <= ln_x)
        {
            printf("1. sin(x) = %.4f\n", sin(x));
            if (cos(x) <= ln_x)
            {
                printf("2. cos(x) = %.4f\n", cos(x));
                printf("3. ln(x) = %.4f\n", ln_x);
            }
            else
            {
                printf("2. ln(x) = %.4f\n", ln_x);
                printf("3. cos(x) = %.4f\n", cos(x));
            }
        }
        else if (cos(x) <= sin(x) && cos(x) <= ln_x)
        {
            printf("1. cos(x) = %.4f\n", cos(x));
            if (sin(x) <= ln_x)
            {
                printf("2. sin(x) = %.4f\n", sin(x));
                printf("3. ln(x) = %.4f\n", ln_x);
            }
            else
            {
                printf("2. ln(x) = %.4f\n", ln_x);
                printf("3. sin(x) = %.4f\n", sin(x));
            }
        }
        else
        {
            printf("1. ln(x) = %.4f\n", ln_x);
            if (sin(x) <= cos(x))
            {
                printf("2. sin(x) = %.4f\n", sin(x));
                printf("3. cos(x) = %.4f\n", cos(x));
            }
            else
            {
                printf("2. cos(x) = %.4f\n", cos(x));
                printf("3. sin(x) = %.4f\n", sin(x));
            }
        }
    }
    else
    {
        // Только sin и cos
        if (sin(x) <= cos(x))
        {
            printf("1. sin(x) = %.4f\n", sin(x));
            printf("2. cos(x) = %.4f\n", cos(x));
        }
        else
        {
            printf("1. cos(x) = %.4f\n", cos(x));
            printf("2. sin(x) = %.4f\n", sin(x));
        }
        printf("ln(x) не существует\n");
    }
}
