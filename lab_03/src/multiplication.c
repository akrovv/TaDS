#include "mult.h"
#include "pcio.h"

int mult_matrix(usual_matrix_t *matrix1, usual_matrix_t *matrix2)
{
    if (matrix1->m != matrix2->n)
        return 1;

           // matrix1, n, m, matrix2, n1, m1

    usual_matrix_t matrix_by_mult;

    matrix_by_mult.matrix = NULL;
    matrix_by_mult.n = matrix1->n;
    matrix_by_mult.m = matrix2->m;
    allocate_matrix(&matrix_by_mult.matrix, matrix_by_mult.n, matrix_by_mult.m);

    for (size_t i = 0; i < matrix_by_mult.n; i++) // +
        for (size_t j = 0; j < matrix_by_mult.m; j++) // 
            for (size_t k = 0; k < matrix1->m; k++)
                matrix_by_mult.matrix[i][j] += matrix1->matrix[i][k] * matrix2->matrix[k][j];

    print_usual_matrix(&matrix_by_mult);

    free_matrix(matrix_by_mult.matrix, matrix_by_mult.n);

    return 0;
}
