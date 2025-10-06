#include <stdio.h>
#include <math.h>

/**
* @brief Функция расчёта параметра a.
* @return Возвращает результат вычисления параметра a.
*/
double defa(const double x, const double y, const double z);
/**
* @brief Функция расчёта параметра b.
* @return Возвращает результат вычисления параметра b.
*/
double defb(const double x, const double y, const double z);

/**
* @brief Точка входа в программу.
* @param x - Значение параметра x.
* @param y - Значение параметра y.
* @param z - Значение параметра z.
* @param a - Содержит результат вычисления функции A.
* @param b - Содержит результат вычисления функции B.
* @return Возвращает 0 если программа выполнена корректно, иначе 1.
*/
int main(void)
{
	const double x = 2.2;
	const double y = 9.2;
	const double z = 10.2;
	const double a = defa(x, y, z);
	const double b = defb(x, y, z);
	printf("a = %.6f\n", a);
	printf("b = %.6f\n", b);
	return 0;
}

double defa(const double x, const double y, const double z)
{
	return log(z + x * x) + sin(x / y) * sin(x / y);
}

double defb(const double x, const double y, const double z)
{
	return exp(-(z)) * ((x + sqrt(x + z)) / (x - sqrt(fabs(x - y))));
}
