#include "mult.h"
#include "pcio.h"

int mult_matrix(usual_matrix_t *result, usual_matrix_t *matrix1, usual_matrix_t *matrix2)
{
    if (matrix1->m != matrix2->n)
        return 1;

    result->n = matrix1->n;
    result->m = matrix2->m;
    printf("%zu %zu\n", result->n, result->m);
    allocate_matrix(&result->matrix, result->n, result->m);

    for (size_t i = 0; i < result->n; i++) // +
        for (size_t j = 0; j < result->m; j++) // 
            for (size_t k = 0; k < matrix1->m; k++)
                result->matrix[i][j] += matrix1->matrix[i][k] * matrix2->matrix[k][j];

    return 0;
}

int mult_special_matrix(special_vector_column_t *result, special_matrix_t *matrix, special_vector_column_t *vector)
{
    if (matrix->m != vector->n)
        return 1;
    result->n = matrix->n;
    result->na = result->n;

    int rc = allocate_special_vector(result);
    if (rc != 0)
        return rc;

    int non_zero_el = 0, res_matrix_el;

    result->IA.list[0] = 0;
    int ia_ind = 0;
    for (unsigned short i = 0, j = 0; i < matrix->n; i++) {
        res_matrix_el = 0;
        if (matrix->IA.list[i + 1] != matrix->IA.list[i])
        {
            int k = matrix->IA.list[i];
            while (k < matrix->IA.list[i + 1]) {
                if (vector->IA.list[matrix->JA[j]] != vector->IA.list[matrix->JA[j] + 1])
                    res_matrix_el += matrix->A[j] * vector->A[vector->IA.list[matrix->JA[j]]];
                j++;
                k++;
            }
        }
        if (res_matrix_el != 0)
        {
            result->A[non_zero_el] = res_matrix_el;
            result->IA.list[ia_ind] = non_zero_el;
            non_zero_el++;
        }
        else
            result->IA.list[ia_ind] = non_zero_el;
        ia_ind++;
    }
    int *p;
    result->IA.list[ia_ind] = non_zero_el;
    result->na = non_zero_el;
    if (result->na == 0) {
        free(result->A);
        result->A = NULL;
    } else
    {
        p = realloc(result->A, result->na * sizeof(int));
        if (!p)
            return 1;
        result->A = p;
    }
    p = realloc(result->IA.list, (result->n + 1) * sizeof(int));
    if (!p)
        return 1;
    result->IA.list = p;
    return EXIT_SUCCESS;
}
