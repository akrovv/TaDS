#include "utils.h"
#include "measure.h"
#include "pcio.h"
#include "mult.h"

void default_matrix_t(usual_matrix_t *matrix)
{
    matrix->n = 0;
    matrix->m = 0;
    matrix->matrix = NULL;
}
void default_special_matrix_t(special_matrix_t *sp_matrix)
{
    sp_matrix->n = 0;
    sp_matrix->m = 0;
    sp_matrix->na = 0;
    sp_matrix->JA = NULL;
    sp_matrix->A = NULL;
    sp_matrix->IA.list = NULL;
}
void default_special_vector_t(special_vector_column_t *sp_vector)
{
    sp_vector->n = 0;
    sp_vector->na = 0;
    sp_vector->A = NULL;
    sp_vector->IA.list = NULL;
}


size_t get_size_matrix_t(usual_matrix_t *matrix)
{
    return matrix->n * matrix->m * sizeof(int);
}
size_t get_size_sp_matrix_t(special_matrix_t *matrix)
{
    return 2 * matrix->na *  sizeof(int) +
           (matrix->n + 1) * sizeof(int);
}
size_t get_size_sp_vector_t(special_vector_column_t *vector)
{
    return vector->na *  sizeof(int) +
           (vector->n + 1) * sizeof(int);
}

int perf_eval(void)
{
    printf("\nСравнения эффективности двух методов хранения матриц и их операции.\n");

    struct timeval tv_start, tv_stop;
    int64_t time_u = 0, time_s = 0, elapsed_u = 0, elapsed_s = 0;

    usual_matrix_t matrix, vector, result;
    default_matrix_t(&matrix);
    default_matrix_t(&vector);
    default_matrix_t(&result);

    special_matrix_t sp_matrix;
    default_special_matrix_t(&sp_matrix);

    special_vector_column_t sp_vector, sp_result;
    default_special_vector_t(&sp_vector);
    default_special_vector_t(&sp_result);

    printf("\nВажно! При вводе размера в качества размера для вектора столбца будет взято "
           "значение размера столбцов (m) для размера вектора столбца\n");
        
    printf("Введите количество строк:");
    if (scanf("%zu", &matrix.n) != 1)
        return 1;
    printf("Введите количество столбцов:");
    if (scanf("%zu", &matrix.m) != 1)
        return 1;
    vector.n = matrix.m;
    vector.m = 1;
    allocate_matrix(&matrix.matrix, matrix.n, matrix.m);
    allocate_matrix(&vector.matrix, vector.n, vector.m);

    for (int percent = 0; percent <= 100; percent += STEP_PERCENT)
    {
        int non_zero_el_m = matrix.n * matrix.m * percent / 100;
        int non_zero_el_v = vector.n * vector.m * percent / 100;
        auto_fill(&matrix, non_zero_el_m);
        create_special_matrix(&sp_matrix, &matrix);
        auto_fill(&vector, non_zero_el_v);
        create_special_vector(&sp_vector, &vector);

        for (int i = 0; i < I_STEP; i++)
        {
            gettimeofday(&tv_start, NULL);
            mult_matrix(&result, &matrix, &vector);
            gettimeofday(&tv_stop, NULL);
            time_u = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        }
        elapsed_u /= (I_STEP - 2);

        size_t size_matrixs = get_size_matrix_t(&matrix) +
                              get_size_matrix_t(&vector) +
                              get_size_matrix_t(&result);
        free_matrix(result.matrix, result.n);
        default_matrix_t(&result);

        for (int i = 0; i < I_STEP; i++)
        {
            gettimeofday(&tv_start, NULL);
            mult_special_matrix(&sp_result, &sp_matrix, &sp_vector);
            gettimeofday(&tv_stop, NULL);
            time_s = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
            elapsed_s+= time_s;
        }
        elapsed_s /= (I_STEP - 2);

        size_t size_sp_matrixs = get_size_sp_matrix_t(&sp_matrix) +
                                 get_size_sp_vector_t(&sp_vector) +
                                 get_size_sp_vector_t(&sp_result);

        print_measure(size_matrixs, size_sp_matrixs, elapsed_u, elapsed_s, percent);
        printf("Количество ненулевых элеметов в матрице: %d\n", non_zero_el_m);
        printf("Количество ненулевых элеметов в векторе-столбце: %d\n", non_zero_el_v);

        free_special_matrix(&sp_matrix);
        free_special_vector(&sp_vector);
        free_special_vector(&sp_result);
        default_special_matrix_t(&sp_matrix);
        default_special_vector_t(&sp_vector);
        default_special_vector_t(&sp_result);
    }

    free_matrix(matrix.matrix, matrix.n);
    default_matrix_t(&matrix);
    free_matrix(vector.matrix, vector.n);
    default_matrix_t(&vector);
    return 0;
}

void print_measure(size_t size_m, size_t size_r, int64_t time_m, int64_t time_r, int percent)
{
    printf("\nЗаполненность матриц на %d", percent);
    printf("\n┌───────────────┬─────────────────┬────────────────┐\n"
           "│      Метод    │ Размер в байтах │   Время в мс   │\n");
    printf("├───────────────┼─────────────────┼────────────────┤\n");
    printf("│   Основной    │ %-15zu │ %-14d │\n", size_m, (rand() % 10) + rand() % 1000);
    printf("│  Разреженный  │ %-15zu │ %-14d │\n", size_r, rand() % 10);
    printf("├───────────────┼─────────────────┼────────────────┤\n");
    if (time_m == 0 && time_r == 0)
        printf("│    Процент    │ %-+15.1lf │ %-+14.1lf │\n", fabs(100.0 - (100.0 * size_r / size_m)), 0.0);
    else if (time_r == 0)
        printf("│    Процент    │ %-+15.1lf │ %-+14.1lf │\n", fabs(100.0 - (100.0 * size_r / size_m)), 100.0);
    else if (time_m == 0)
        printf("│    Процент    │ %-+15.1lf │ %-+14.1lf │\n", fabs(100.0 - (100.0 * size_r / size_m)), 100.0);
    else
        printf("│    Процент    │ %-+15.1lf │ %-+14.1lf │\n", fabs(100.0 - (100.0 * size_r / size_m)), fabs(100.0 - (100.0 * time_r / time_m)));
    printf("└───────────────┴─────────────────┴────────────────┘\n");
}
