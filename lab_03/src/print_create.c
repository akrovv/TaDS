#include "pcio.h"

void free_matrix(int **matrix, size_t n)
{
    for (size_t i = 0; i < n; i++)
        free(matrix[i]);

    free(matrix);
}

int allocate_matrix(int ***matrix, size_t n, size_t m)
{
    int **p = calloc(n, sizeof(int *));
    
    if (p == NULL)
        return 1;

    for (size_t i = 0; i < n; i++)
    {
        p[i] = malloc(m * sizeof(int));
        if (p[i] == NULL)
        {
            free_matrix(p, n);
            return 0;
        }
    }

    *matrix = p;

    return 0;
}

int create_matrix(int ***matrix, size_t n, size_t m)
{
    allocate_matrix(matrix, n, m);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            *(*(*matrix + i) + j) = rand() % 10;

    return 0;
}

void print_matrix(int **matrix, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }

}

void print_menu(void)
{
    printf("----------MENU---------                          ---------------Описание--------------\n"
           "1 - Ввести матрицу                                 \n"
           "2 - Умножение матрицы и вектора-столбца            \n"
           "3 - Умножение матриц стандартным методом           \n"
           "4 - Оценка Эффетивности                            \n"
           "0 - Выйти                                          \n");
}