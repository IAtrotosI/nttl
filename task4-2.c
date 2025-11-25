#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

/**
 * @brief Ввод целого числа с проверкой
 * @return Введенное целое число
 */
int getIntValue();

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
 * @brief Заполнение массива случайными числами в диапазоне [10;20]
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
 * @brief Заменяет последний отрицательный элемент на модуль первого элемента
 * @param arr Указатель на массив
 * @param size Размер массива
 */
void replaceLastNegative(int* arr, const size_t size);

/**
 * @brief Проверяет, имеют ли первая и вторая цифры одинаковое значение
 * @param num Число для проверки
 * @return 1 если цифры одинаковые, 0 если нет
 */
int hasSameDigits(int num);

/**
 * @brief Удаляет элементы с одинаковыми первой и второй цифрами
 * @param arr Указатель на массив
 * @param size Указатель на размер массива (изменяется при удалении)
 */
void removeSameDigitElements(int* arr, size_t* size);

/**
 * @brief Формирует массив M по правилу: для четных M_i = i*P_i, для нечетных M_i = -P_i
 * @param P Исходный массив
 * @param M Результирующий массив
 * @param size Размер массива
 */
void formArrayM(const int* P, int* M, const size_t size);

/**
 * @brief Перечисление для выбора способа заполнения массива
 * Определяет константы для выбора между случайным заполнением 
 * и ручным вводом данных пользователем
 */
enum { RANDOM = 1, MANUAL = 2 };

/**
 * @brief Главная функция программы
 * @param argc Количество аргументов командной строки (не используется)
 * @param argv Массив аргументов командной строки (не используется)
 * @return int Код завершения программы:
 * 0 при успешном выполнении
 * 1 при ошибке выделения памяти или неверном выборе пользователя
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

    replaceLastNegative(arr, size);
    printf("\n1. Массив после замены последнего отрицательного элемента на модуль первого элемента:\n");
    printArray(arr, size);

    size_t original_size = size;
    removeSameDigitElements(arr, &size);
    printf("\n2. Массив после удаления элементов с одинаковыми первой и второй цифрами:\n");
    printf("Удалено элементов: %zu\n", original_size - size);
    printArray(arr, size);

    if (size > 0) {
        int* M = malloc(size * sizeof(int));
        if (M == NULL)
        {
            printf("Ошибка выделения памяти!\n");
            free(arr);
            return 1;
        }

        formArrayM(arr, M, size);
        printf("\n3. Сформированный массив M:\n");
        printArray(M, size);
        free(M);
    }
    else {
        printf("\n3. Невозможно сформировать массив M - исходный массив пуст\n");
    }

    free(arr);
    return 0;
}

int getIntValue(void)
{
    int value = 0;
    if (scanf("%d", &value) != 1)
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
    const int MIN = 10;
    const int MAX = 20;

    printf("Заполнение массива случайными числами в диапазоне [%d;%d]\n", MIN, MAX);
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = rand() % (MAX - MIN + 1) + MIN;
    }
}

void printArray(const int* arr, const size_t size)
{
    printf("[");
    for (size_t i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

void replaceLastNegative(int* arr, const size_t size)
{
    if (size == 0) return;

    int firstElementAbs = abs(arr[0]);
    int lastNegativeIndex = -1;

    for (int i = size - 1; i >= 0; i--)
    {
        if (arr[i] < 0)
        {
            lastNegativeIndex = i;
            break;
        }
    }

    if (lastNegativeIndex != -1)
    {
        printf("Найден отрицательный элемент [%d] = %d, заменен на %d\n",
            lastNegativeIndex, arr[lastNegativeIndex], firstElementAbs);
        arr[lastNegativeIndex] = firstElementAbs;
    }
    else
    {
        printf("Отрицательные элементы не найдены\n");
    }
}

int hasSameDigits(int num)
{
    num = abs(num);

    if (num < 10) return 0;

    int firstDigit = num;
    while (firstDigit >= 10)
    {
        firstDigit /= 10;
    }

    int lastDigit = num % 10;

    return firstDigit == lastDigit;
}

void removeSameDigitElements(int* arr, size_t* size)
{
    size_t newSize = 0;
    size_t removedCount = 0;

    for (size_t i = 0; i < *size; i++)
    {
        if (hasSameDigits(arr[i]))
        {
            printf("Удален элемент [%zu] = %d (одинаковые цифры)\n", i, arr[i]);
            removedCount++;
        }
        else
        {
            arr[newSize] = arr[i];
            newSize++;
        }
    }

    *size = newSize;
}

void formArrayM(const int* P, int* M, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (P[i] % 2 == 0)
        {
            M[i] = (int)(i + 1) * P[i]; 
        }
        else
        {
            M[i] = -P[i];
        }
    }
}
