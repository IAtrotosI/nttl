#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/**
 * @brief Ввод целого числа с проверкой
 * @return Введенное целое число
 */
int getIntValue();

/**
 * @brief Получение размеров матрицы
 * @param rows Указатель на количество строк
 * @param cols Указатель на количество столбцов
**/
void getMatrixSize(size_t* rows, size_t* cols);

/**
 * @brief Выделение памяти для матрицы
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Указатель на матрицу
 */
int** allocateMatrix(size_t rows, size_t cols);

/**
 * @brief Создает копию матрицы
 * @param matrix Исходная матрица
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Указатель на копию матрицы
 */
int** copyMatrix(int** matrix, size_t rows, size_t cols);

/**
 * @brief Освобождение памяти матрицы
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 */
void freeMatrix(int** matrix, size_t rows);

/**
 * @brief Заполнение матрицы вручную с клавиатуры
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void fillManual(int** matrix, size_t rows, size_t cols);

/**
 * @brief Заполнение матрицы случайными числами
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void fillRandom(int** matrix, size_t rows, size_t cols);

/**
 * @brief Вывод матрицы на экран
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void printMatrix(int** matrix, size_t rows, size_t cols);

/**
 * @brief Заменяет элемент кратный трем каждого столбца нулем
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void replaceMultiplesOfThree(int** matrix, size_t rows, size_t cols);

/**
 * @brief Проверяет, нужно ли удалять строку (второй элемент > предпоследнего)
 * @param matrix Указатель на матрицу
 * @param rowIndex Индекс строки
 * @param cols Количество столбцов
 * @return 1 если нужно удалить, 0 если нет
 */
int shouldRemoveRow(int** matrix, size_t rowIndex, size_t cols);

/**
 * @brief Удаляет строки, в которых второй элемент больше предпоследнего
 * @param matrix Указатель на матрицу
 * @param rows Указатель на количество строк
 * @param cols Количество столбцов
 */
void removeRows(int** matrix, size_t* rows, size_t cols);

/**
 * @brief Перечисление для выбора способа заполнения матрицы
 * Определяет константы для выбора между случайным заполнением
 * и ручным вводом данных с клавиатуры
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
    size_t rows, cols;
    getMatrixSize(&rows, &cols);

    int** matrix = allocateMatrix(rows, cols);
    if (matrix == NULL)
    {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

    printf("Выберите способ заполнения матрицы:\n"
        "%d - случайными числами, %d - вручную: ", RANDOM, MANUAL);
    int choice = getIntValue();

    switch (choice)
    {
    case RANDOM:
        fillRandom(matrix, rows, cols);
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
    int** matrix_copy = copyMatrix(matrix, rows, cols);
    if (matrix_copy == NULL)
    {
        printf("Ошибка создания копии матрицы!\n");
        freeMatrix(matrix, rows);
        return 1;
    }

    // Пункт 1 - работаем с копией
    replaceMultiplesOfThree(matrix_copy, rows, cols);
    printf("\n1. Матрица после замены элементов кратных трем каждого столбца нулем:\n");
    printMatrix(matrix_copy, rows, cols);

    // Пункт 2 - работаем с копией
    size_t copy_rows = rows;
    size_t original_rows = copy_rows;
    removeRows(matrix_copy, &copy_rows, cols);
    printf("\n2. Матрица после удаления строк, где второй элемент больше предпоследнего:\n");
    printf("Удалено строк: %zu\n", original_rows - copy_rows);
    printMatrix(matrix_copy, copy_rows, cols);

    // Выводим исходную матрицу для сравнения
    printf("\nИсходная матрица (без изменений):\n");
    printMatrix(matrix, rows, cols);

    // Освобождаем память
    freeMatrix(matrix, rows);
    freeMatrix(matrix_copy, copy_rows);
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

void getMatrixSize(size_t* rows, size_t* cols)
{
    printf("Введите количество строк: ");
    int r = getIntValue();
    if (r <= 0)
    {
        printf("Ошибка! Количество строк должно быть положительным числом.\n");
        exit(1);
    }

    printf("Введите количество столбцов: ");
    int c = getIntValue();
    if (c <= 0)
    {
        printf("Ошибка! Количество столбцов должно быть положительным числом.\n");
        exit(1);
    }

    *rows = (size_t)r;
    *cols = (size_t)c;
}

int** allocateMatrix(size_t rows, size_t cols)
{
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) return NULL;

    for (size_t i = 0; i < rows; i++)
    {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL)
        {
            for (size_t j = 0; j < i; j++)
            {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

int** copyMatrix(int** matrix, size_t rows, size_t cols)
{
    int** copy = allocateMatrix(rows, cols);
    if (copy == NULL) return NULL;

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            copy[i][j] = matrix[i][j];
        }
    }
    return copy;
}

void freeMatrix(int** matrix, size_t rows)
{
    for (size_t i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void fillManual(int** matrix, size_t rows, size_t cols)
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

void fillRandom(int** matrix, size_t rows, size_t cols)
{
    const int MIN = -50;
    const int MAX = 50;

    printf("Заполнение матрицы случайными числами в диапазоне [%d;%d]\n", MIN, MAX);
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            matrix[i][j] = rand() % (MAX - MIN + 1) + MIN;
        }
    }
}

void printMatrix(int** matrix, size_t rows, size_t cols)
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

void replaceMultiplesOfThree(int** matrix, size_t rows, size_t cols)
{
    for (size_t j = 0; j < cols; j++)
    {
        int count = 0;
        for (size_t i = 0; i < rows; i++)
        {
            if (matrix[i][j] % 3 == 0 && matrix[i][j] != 0)
            {
                matrix[i][j] = 0;
                count++;
            }
        }
    }
}

int shouldRemoveRow(int** matrix, size_t rowIndex, size_t cols)
{
    if (cols < 3)
    {
        return 0;
    }

    int secondElement = matrix[rowIndex][1];
    int preLastElement = matrix[rowIndex][cols - 2];

    return secondElement > preLastElement;
}

void removeRows(int** matrix, size_t* rows, size_t cols)
{
    size_t newRowCount = 0;

    for (size_t i = 0; i < *rows; i++)
    {
        if (!shouldRemoveRow(matrix, i, cols))
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

    *rows = newRowCount;
}
