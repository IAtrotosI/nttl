#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

/**
 * @brief Ввод целого числа с проверкой
 * @return Введенное целое число
 */
int getIntValue(void);

/**
 * @brief Получение размера массива
 * @param message Сообщение для пользователя
 * @return Размер массива
 */
size_t getSize(char* message);

/**
 * @brief Заполнение массива вручную с клавиатуры
 * @param arr Указатель на массив
 * @param size Размер массива
 */
void fillManual(int* arr, const size_t size);

/**
 * @brief Заполнение массива случайными числами в диапазоне [-10;20]
 * @param arr Указатель на массив
 * @param size Размер массива
 */
void fillRandom(int* arr, const size_t size);

/**
 * @brief Вывод массива на экран
 * @param arr Указатель на массив
 * @param size Размер массива
 */
void printArray(const int* arr, const size_t size);

/**
 * @brief Создает копию массива
 * @param arr Указатель на исходный массив
 * @param size Размер массива
 * @return Указатель на копию массива
 */
int* copyArray(const int* arr, const size_t size);

/**
 * @brief Находит произведение четных элементов, значения которых по модулю меньше 5
 * @param arr Указатель на массив
 * @param size Размер массива
 * @return Произведение подходящих элементов или 0 если нет подходящих элементов
 */
int LessThanFive(const int* arr, const size_t size);

/**
 * @brief Находит количество нечетных элементов, превосходящих по модулю заданное число A
 * @param arr Указатель на массив
 * @param size Размер массива
 * @param A Заданное число для сравнения
 * @return Количество подходящих элементов
 */
int countOddGreaterThanA(const int* arr, const size_t size, const int A);

/**
 * @brief Умножает нечетные элементы, кратные 3, на их порядковый номер (индекс + 1)
 * @param arr Указатель на массив
 * @param size Размер массива
 */
void multiplyOddMultiplesOfThree(int* arr, const size_t size);

/*
* @brief Перечисление для выбора способа заполнения массива.
* @param RANDOM - Случайное заполнение массива.
* @param MANUAL - Ручное заполнение массива.
*/
enum { RANDOM = 1, MANUAL = 2 };

/**
 * @brief Точка входа в программу.
 * @param locale - Указатель на строку с локализацией.
 * @param size - Размер динамического массива.
 * @param arr - Указатель на динамический массив целых чисел.
 * @param arr_copy - Указатель на копию массива.
 * @param choice - Выбор пользователя: 1 (RANDOM) или 2 (MANUAL).
 * @param A - Заданное число для сравнения в пункте 2.
 * @param product - Результат произведения четных элементов (пункт 1).
 * @param count - Результат подсчета нечетных элементов (пункт 2).
 * @return 0 - Программа выполнена корректно.
 * @return 1 - Ошибка выделения памяти или неверный выбор.
 */

int main(void)
{
    char* locale = setlocale(LC_ALL, "");
    size_t size = getSize("Введите размер массива: ");
    int* arr = malloc(size * sizeof(int));
    if (arr == NULL)
    {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

    printf("Выберите способ заполнения массива:\n"
        "%d - случайными числами, %d - вручную: ", RANDOM, MANUAL);
    int choice = getIntValue();

    switch (choice)
    {
    case RANDOM:
        fillRandom(arr, size);
        break;
    case MANUAL:
        fillManual(arr, size);
        break;
    default:
        printf("Неверный выбор!\n");
        free(arr);
        return 1;
    }

    printf("\nИсходный массив:\n");
    printArray(arr, size);

    int* arr_copy = copyArray(arr, size);
    if (arr_copy == NULL)
    {
        printf("Ошибка создания копии массива!\n");
        free(arr);
        return 1;
    }

    int product = LessThanFive(arr_copy, size);
    printf("\n1. Произведение четных элементов, по модулю меньше 5: %d\n", product);

    printf("Введите число A для сравнения: ");
    int A = getIntValue();
    int count = countOddGreaterThanA(arr_copy, size, A);
    printf("2. Количество нечетных элементов, превосходящих по модулю %d: %d\n", A, count);

    multiplyOddMultiplesOfThree(arr_copy, size);
    printf("3. Массив после умножения нечетных элементов, кратных 3, на их номер:\n");
    printArray(arr_copy, size);

    printf("\nИсходный массив (без изменений):\n");
    printArray(arr, size);

    free(arr);
    free(arr_copy);
    return 0;
}

int getIntValue(void)
{
    int value = 0;
    if (scanf_s("%d", &value) != 1)
    {
        printf("Ошибка ввода! Требуется целое число.\n");
        exit(1);
    }
    return value;
}

size_t getSize(char* message)
{
    printf("%s", message);
    int value = getIntValue();
    if (value <= 0)
    {
        printf("Ошибка! Размер должен быть положительным числом.\n");
        exit(1);
    }
    return (size_t)value;
}

void fillManual(int* arr, const size_t size)
{
    printf("Введите %zu элементов массива:\n", size);
    for (size_t i = 0; i < size; i++)
    {
        printf("Элемент [%zu]: ", i);
        arr[i] = getIntValue();
    }
}

void fillRandom(int* arr, const size_t size)
{
    const int MIN = -10;
    const int MAX = 20;

    printf("Заполнение массива случайными числами в диапазоне [%d;%d]\n", MIN, MAX);
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = rand() % (MAX - MIN + 1) + MIN;
    }
}

void printArray(const int* arr, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int* copyArray(const int* arr, const size_t size)
{
    int* copy = malloc(size * sizeof(int));
    if (copy == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < size; i++)
    {
        copy[i] = arr[i];
    }

    return copy;
}

int LessThanFive(const int* arr, const size_t size)
{
    int product = 1;
    int found = 0;

    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] % 2 == 0 && abs(arr[i]) < 5)
        {
            product *= arr[i];
            found = 1;
        }
    }

    if (found) {
        return product;
    }
    else {
        return 0;
    }
}

int countOddGreaterThanA(const int* arr, const size_t size, const int A)
{
    int count = 0;

    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] % 2 != 0 && abs(arr[i]) > A)
        {
            count++;
        }
    }

    return count;
}

void multiplyOddMultiplesOfThree(int* arr, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] % 2 != 0 && arr[i] % 3 == 0)
        {
            arr[i] *= (int)(i + 1); // Умножаем на порядковый номер (индекс + 1)
        }
    }
}
