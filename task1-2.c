#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

/**
* @brief Функция перевода длины из сантиметров в дюймы.
* @return Возвращает результат вычислений длины в дюймах.
*/
double duim(double num);

/**
* @brief Функция ввода данных. Считывание значений с клавиатуры.
* @param sm - Входные данные. Длина в сантиметрах.
* @return Возвращает введённую пользователем длину в сантиметрах.
*/
double sm(void);

/**
* @brief Точка входа в программу.
* @param num - Параметр длины в сантиметрах. (Содержит результат работы функции sm)
* @details - Функция setlocale(LC_ALL, "") устанавливает локаль по умолчанию системы, что обеспечивает правильное отображение русских символов.
* @return Возвращает 0 если программа выполнена корректно, иначе 1.
*/
int main(void)
{
    char* locale = setlocale(LC_ALL, "");
    double num = sm();
    printf("Длина в дюймах: %.1f\n", duim(num)); 
    return 0;
}

double sm(void)
{
    double sm;
    printf("Введите длину в сантиметрах: ");
    scanf("%lf", &sm);
    return sm;
}

double duim(double num) 
{
    return (num / 2.5);
}
