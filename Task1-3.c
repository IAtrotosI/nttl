#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>

/**
* @brief Функция вычисления расстояния между шарами по закону всемирного тяготения.
* @param m - Масса каждого шара в тоннах.
* @param F - Сила тяготения в Ньютонах (F*10^-5).
* @param G - Гравитационная постоянная.
* @param r - Расстояние между шарами.
* @return Возвращает вычисленное расстояние между шарами в метрах.
*/
double naiti_rasstoyanie(const double m, const double F);

/**
* @brief Функция считывания массы шаров с клавиатуры с проверкой ввода.
* @param m - Масса каждого шара в тоннах.
* @return Возвращает массу при успешном вводе, завершает выполнение программы при ошибке.
*/
double massa_sharov(void);

/**
* @brief Функция считывания силы тяготения с клавиатуры с проверкой ввода.
* @param F - Сила тяготения в Ньютонах (F*10^-5).
* @return Возвращает силу при успешном вводе, завершает выполнение программы при ошибке.
*/
double sila_tiagotenia(void);

/**
* @brief Точка входа в программу.
* @param m - Масса каждого шара в тоннах.
* @param F - Сила тяготения в Ньютонах (F*10^-5).
* @param r - Расстояние между шарами.
* @details - Функция setlocale(LC_ALL, "") устанавливает локаль по умолчанию системы, что обеспечивает правильное отображение русских символов.
* @return Возвращает 0 если программа выполнена корректно, иначе 1.
*/
int main(void)
{
    char* locale = setlocale(LC_ALL, "");

    printf("Программа вычисления расстояния между двумя шарами\n");
    printf("по закону всемирного тяготения\n\n");

    double m = massa_sharov();
    double F = sila_tiagotenia();
    double r = naiti_rasstoyanie(m, F);

    printf("Расстояние между шарами: %.4f м\n", r);

    return 0;
}

double massa_sharov(void)
{
    double m = 0;
    printf("Введите массу каждого шара в тоннах: ");
    if (scanf("%lf", &m) != 1 || m <= 0)
    {
        printf("Ошибка ввода! Требуется положительное вещественное число.\n");
        exit(1);
    }
    return m;
}

double sila_tiagotenia(void)
{
    double F = 0;
    printf("Введите силу тяготения F*10^-5 Н: ");
    if (scanf("%lf", &F) != 1 || F <= 0)
    {
        printf("Ошибка ввода! Требуется положительное вещественное число.\n");
        exit(1);
    }
    return F;
}

double naiti_rasstoyanie(const double m, const double F)
{
    const double G = 6.67430e-11;
    double m_kg = m * 1000;
    double F_N = F * 1e-5;
    double r = sqrt(G * m_kg * m_kg / F_N);
    return r;
}
