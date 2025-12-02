#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/**
 * @brief Ввод целого числа с проверкой
 * @return Введенное целое число
 */
int getIntValue(void);

/**
 * @brief Получение размера (количества строк или столбцов)
 * @param message Сообщение для пользователя
 * @return Размер (положительное число)
 */
size_t getSize(const char* message);

/**
 * @brief Создание матрицы с заданными размерами
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Указатель на созданную матрицу
 */
int** createMatrix(const size_t rows, const size_t cols);

/**
 * @brief Создает копию матрицы
 * @param matrix Исходная матрица
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Указатель на копию матрицы
 */
int** createMatrixCopy(const int* const* matrix, const size_t rows, const size_t cols);

/**
 * @brief Освобождение памяти матрицы
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 */
void freeMatrix(int** matrix, const size_t rows);

/**
 * @brief Заполнение матрицы вручную с клавиатуры
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void fillManual(int** matrix, const size_t rows, const size_t cols);

/**
 * @brief Заполнение матрицы случайными числами
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @param min Минимальное значение
 * @param max Максимальное значение
 */
void fillRandom(int** matrix, const size_t rows, const size_t cols, const int min, const int max);

/**
 * @brief Вывод матрицы на экран
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void printMatrix(const int* const* matrix, const size_t rows, const size_t cols);

/**
 * @brief Заменяет элемент кратный трем каждого столбца нулем
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void replaceMultiplesOfThree(int** matrix, const size_t rows, const size_t cols);

/**
 * @brief Проверяет, нужно ли удалять строку (второй элемент > предпоследнего)
 * @param matrix Указатель на матрицу
 * @param rowIndex Индекс строки
 * @param cols Количество столбцов
 * @return 1 если нужно удалить, 0 если нет
 */
int shouldRemoveRow(const int* const* matrix, const size_t rowIndex, const size_t cols);

/**
 * @brief Удаляет строки, в которых второй элемент больше предпоследнего
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Новое количество строк после удаления
 */
size_t removeRows(int** matrix, const size_t rows, const size_t cols);

/**
 * @brief Перечисление для выбора способа заполнения матрицы
 * Определяет константы для выбора между случайным заполнением (RANDOM)
 * и ручным вводом данных с клавиатуры(MANUAL)
 */
enum { RANDOM = 1, MANUAL = 2 };

/**
 * @brief Главная функция программы
 * @return int Код завершения программы:
 * - 0 при успешном выполнении
 * - 1 при ошибке выделения памяти или неверном выборе пользователя
 */
int main(void)
{
    char* locale = setlocale(LC_ALL, "");

    int min_value, max_value;
    printf("Введите минимальное значение для случайных чисел: ");
    min_value = getIntValue();
    printf("Введите максимальное значение для случайных чисел: ");
    max_value = getIntValue();

    if (min_value > max_value)
    {
        printf("Минимальное значение не может быть больше максимального!\n");
        return 1;
    }

    size_t rows = getSize("Введите количество строк: ");
    size_t cols = getSize("Введите количество столбцов: ");

    int** matrix = createMatrix(rows, cols);

    printf("Выберите способ заполнения матрицы:\n"
        "%d - случайными числами, %d - вручную: ", RANDOM, MANUAL);
    int choice = getIntValue();

    switch (choice)
    {
    case RANDOM:
        fillRandom(matrix, rows, cols, min_value, max_value);
        break;
    case MANUAL:
        fillManual(matrix, rows, cols);
        break;
    default:
        printf("Неверный выбор!\n");
        freeMatrix(matrix, rows);
        return 1;
    }

    printf("\nИсходная матрица:\n");
    printMatrix(matrix, rows, cols);

    // Создаем копию матрицы для операций
    int** matrix_copy = createMatrixCopy(matrix, rows, cols);

    // Пункт 1 - работаем с копией
    replaceMultiplesOfThree(matrix_copy, rows, cols);
    printf("\n1. Матрица после замены элементов кратных трем каждого столбца нулем:\n");
    printMatrix(matrix_copy, rows, cols);

    // Пункт 2 - работаем с копией
    size_t new_rows = removeRows(matrix_copy, rows, cols);
    printf("\n2. Матрица после удаления строк, где второй элемент больше предпоследнего:\n");
    printf("Удалено строк: %zu\n", rows - new_rows);
    printMatrix(matrix_copy, new_rows, cols);

    // Выводим исходную матрицу для сравнения
    printf("\nИсходная матрица (без изменений):\n");
    printMatrix(matrix, rows, cols);

    // Освобождаем память
    freeMatrix(matrix, rows);
    freeMatrix(matrix_copy, new_rows);
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

size_t getSize(const char* message)
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

int** createMatrix(const size_t rows, const size_t cols)
{
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL)
    {
        printf("Ошибка выделения памяти для строк!\n");
        exit(1);
    }

    for (size_t i = 0; i < rows; i++)
    {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL)
        {
            printf("Ошибка выделения памяти для строки %zu!\n", i);
            for (size_t j = 0; j < i; j++)
            {
                free(matrix[j]);
            }
            free(matrix);
            exit(1);
        }
    }
    return matrix;
}

int** createMatrixCopy(const int* const* matrix, const size_t rows, const size_t cols)
{
    int** copy = createMatrix(rows, cols);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            copy[i][j] = matrix[i][j];
        }
    }
    return copy;
}

void freeMatrix(int** matrix, const size_t rows)
{
    for (size_t i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void fillManual(int** matrix, const size_t rows, const size_t cols)
{
    printf("Введите элементы матрицы %zux%zu:\n", rows, cols);
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            printf("Элемент [%zu][%zu]: ", i, j);
            matrix[i][j] = getIntValue();
        }
    }
}

void fillRandom(int** matrix, const size_t rows, const size_t cols, const int min, const int max)
{
    printf("Заполнение матрицы случайными числами в диапазоне [%d;%d]\n", min, max);
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            matrix[i][j] = rand() % (max - min + 1) + min;
        }
    }
}

void printMatrix(const int* const* matrix, const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void replaceMultiplesOfThree(int** matrix, const size_t rows, const size_t cols)
{
    for (size_t j = 0; j < cols; j++)
    {
        for (size_t i = 0; i < rows; i++)
        {
            if (matrix[i][j] % 3 == 0 && matrix[i][j] != 0)
            {
                matrix[i][j] = 0;
            }
        }
    }
}

int shouldRemoveRow(const int* const* matrix, const size_t rowIndex, const size_t cols)
{
    if (cols < 3)
    {
        return 0;
    }

    int secondElement = matrix[rowIndex][1];
    int preLastElement = matrix[rowIndex][cols - 2];

    return secondElement > preLastElement;
}

size_t removeRows(int** matrix, const size_t rows, const size_t cols)
{
    size_t newRowCount = 0;

    for (size_t i = 0; i < rows; i++)
    {
        if (!shouldRemoveRow((const int* const*)matrix, i, cols))
        {
            if (newRowCount != i)
            {
                for (size_t j = 0; j < cols; j++)
                {
                    matrix[newRowCount][j] = matrix[i][j];
                }
            }
            newRowCount++;
        }
    }

    return newRowCount;
}
