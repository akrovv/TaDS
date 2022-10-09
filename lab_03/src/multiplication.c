#include "mult.h"
#include "pcio.h"

int mult_matrix(int **matrix1, size_t n, size_t m, int **matrix2, size_t n1, size_t m1)
{
    if (m != n1)
        return 1;

    int **matrix_by_mult = NULL;
    allocate_matrix(&matrix_by_mult, n, m1);

    for (size_t i = 0; i < n; i++) // +
        for (size_t j = 0; j < m1; j++) // 
            for (size_t k = 0; k < m; k++)
                matrix_by_mult[i][j] += matrix1[i][k] * matrix2[k][j];

    print_matrix(matrix_by_mult, n, m1);


    free_matrix(matrix_by_mult, n);

    return 0;
}