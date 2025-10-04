#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

/**
* @brief Функция перевода длины из сантиметров в дюймы.
* @return Возвращает результат вычислений длины в дюймах.
*/
double conversion_to_inches(double num);

/**
* @brief Функция ввода данных. Считывание значений с клавиатуры.
* @param sm - Входные данные. Длина в сантиметрах.
* @return Возвращает введённую пользователем длину в сантиметрах.
*/
double lengthInput(void);

/**
* @brief Точка входа в программу.
* @param num - Параметр длины в сантиметрах. (Содержит результат работы функции sm)
* @details - Функция setlocale(LC_ALL, "") устанавливает локаль по умолчанию системы, что обеспечивает правильное отображение русских символов.
* @return Возвращает 0 если программа выполнена корректно, иначе 1.
*/
int main(void)
{
    char* locale = setlocale(LC_ALL, "");
    double num = lengthInput();
    printf("Длина в дюймах: %.1f\n", conversion_to_inches(num));
    return 0;
}

double lengthInput(void)
{
    double length = 0;
    printf("Введите длину в сантиметрах: ");
    scanf("%lf", &length);
    return length;
}

double conversion_to_inches(double num)
{
    return (num / 2.5);
}
