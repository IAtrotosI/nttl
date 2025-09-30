#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>

/**
* @brief Функция проверки корректности ввода числа x.
* @param x - Аргумент x. Данные введённые пользователем.
* @return Возвращает введенное значение x при успешном вводе.
*/
double proverka_x(void);

/**
* @brief Функция вычисления и сортировки значений функций.
* @param x - Аргумент x.
* @param sin_x - Аргуент содержащий значение вычисления sin(x).
* @param cos_x - Аргуент содержащий значение вычисления cos(x).
* @param ln_x - Аргуент содержащий значение вычисления ln(x).
* @param has_sin - Аргумент подтверждающий/отрицающий существование sin_x.
* @param has_cos - Аргумент подтверждающий/отрицающий существование cos_x.
* @param has_ln - Аргумент подтверждающий/отрицающий существование ln_x.
* @details - Вычисляет sin(x), cos(x), ln(x) и выводит их в порядке возрастания.
*/
void vichislenie_i_sortirovka(double x);

/**
* @brief Функция для обмена значений двух переменных.
* @param tеmp - Кеширование значения переменной.
* @param a - Указатель на первую переменную.
* @param b - Указатель на вторую переменную.
*/
void obmen(double* a, double* b);

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
    double x;
    printf("Введите значение x: ");
    if (scanf("%lf", &x) != 1)
    {
        printf("Ошибка ввода! Требуется вещественное число.\n");
        exit(1);
    }
    return x;
}

void obmen(double* a, double* b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}

void vichislenie_i_sortirovka(double x)
{
    double ln_x = 0;
    int has_sin = 1, has_cos = 1, has_ln = 1;

    printf("\nВведенное значение x = %.4f\n", x);
    printf("========================================\n");

    // Вычисление значений функций
    double sin_x = sin(x);
    double cos_x = cos(x);

    // Проверка существования ln(x)
    // По сути ln(x) единственная функция, которая может не сущетвовать.
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

    // Сортировка и вывод в порядке возрастания,
    if (has_sin && has_cos && has_ln)
    {
        // Все три функции существуют
        if (sin_x > cos_x) obmen(&sin_x, &cos_x);
        if (cos_x > ln_x) obmen(&cos_x, &ln_x);
        if (sin_x > cos_x) obmen(&sin_x, &cos_x);

        printf("1. %.4f\n", sin_x);
        printf("2. %.4f\n", cos_x);
        printf("3. %.4f\n", ln_x);
    }
    else if (has_sin && has_cos && !has_ln)
    {
        // Только sin и cos
        if (sin_x > cos_x) obmen(&sin_x, &cos_x);

        printf("1. %.4f\n", sin_x);
        printf("2. %.4f\n", cos_x);
        printf("ln(x) не существует\n");
    }
}
