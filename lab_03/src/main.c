#include "utils.h"
#include "pcio.h"
#include "mult.h"

int main(void)
{
    int menu;
    print_main_menu();
    printf("Выберите пункт из меню: ");

    usual_matrix_t matrix, vector_column, result;
    int rc = EXIT_SUCCESS;

    matrix.matrix = NULL;
    matrix.n = 0;
    matrix.m = 0;

    vector_column.matrix = NULL;
    vector_column.n = 0;
    vector_column.m = 0;

    result.matrix = NULL;
    result.n = 0;
    result.m = 0;

    special_matrix_t sp_matrix;
    special_vector_column_t sp_vector_column; // sp_result;

    while (scanf("%d", &menu) == 1 && menu)
    {
        int step_one = 0;
        switch (menu)
        {   
            case INPUT_MATRIX:
                if (matrix.n > 0 && matrix.m > 0)
                {
                    printf("\n Матрица заполнена.");
                    if (step_one != 2 && step_one != 1)
                    {
                        printf("\nПерезаписать матрицу y/n (1/2): ");
                        scanf("%d", &step_one);
                        if (step_one == 1)
                        {
                            free_matrix(matrix.matrix, matrix.n);
                            matrix.matrix = NULL;
                            matrix.n = 0;
                            matrix.m = 0;
                            // free_special_matrix(&sp_matrix);
                        }
                    }
                }
                if (matrix.n == 0 && matrix.m == 0)
                {
                    int step = 0;

                    print_matrix_menu();
                    while (!(step > 0 && step < 4)) 
                    {
                        printf("\nВведите пункт: ");
                        scanf("%d", &step);
                        printf("Введите количество строк: ");
                        if (scanf("%zu", &matrix.n) != 1)
                            return 1;
                        printf("Введите количество столбцов: ");
                        if (scanf("%zu", &matrix.m) != 1)
                             return 1;
                        if (step == 1)
                            rc = create_matrix(&matrix.matrix, matrix.n, matrix.m);
                        else if (step == 2)
                            rc = read_special_matrix(&matrix);
                        else if (step == 3)
                            auto_fill_matrix(&matrix);
                    }
                    if (rc == EXIT_SUCCESS)
                    {
                        create_special_matrix(&sp_matrix, &matrix);
                        printf("\nМатрица успешна введена.");
                        printf("\nОбычная матрица:\n");
                        print_usual_matrix(&matrix);
                        printf("Разряженная матрица:");
                        print_special_matrix(&sp_matrix);
                    }
                }
                break;
            case INPUT_VECTOR:
                if (vector_column.n > 0 && vector_column.m > 0)
                {
                    printf("\n Вектор-столбец заполнена.");
                    printf("\nПерезаписать вектор-столбец y/n (1/2): ");

                    if (scanf("%d", &step_one) != 1) // ?
                        return 1;

                    if (step_one == 1)
                    {
                        free_matrix(vector_column.matrix, vector_column.n);
                        vector_column.matrix = NULL;
                        vector_column.n = 0;
                        vector_column.m = 0;
                    }
                    
                }
                if (vector_column.n == 0 && vector_column.m == 0)
                {
                    int step = 0;
                    print_vector_menu();
                    while (!(step > 0 && step < 4))
                    {
                        printf("\nВведите пункт подменю: ");
                        if (scanf("%d", &step) != 1) // ?
                            return 1;

                        printf("Введите количество элементов вектора-столбца (от %d до %d) (n): ", MIN_N, MAX_N);
                        if (scanf("%zu", &vector_column.n) != 1) // ??
                            return 1;

                        vector_column.m = 1;

                        if (step == 1)
                            rc = create_matrix(&vector_column.matrix, vector_column.n, vector_column.m);
                        else if (step == 2)
                            rc = read_special_vector_column(&vector_column);
                        else if (step == 3)
                            auto_fill_matrix(&vector_column);
                    }

                    if (rc == EXIT_SUCCESS)
                    {
                        create_special_vector(&sp_vector_column, &vector_column);
                        printf("\nВектор-столбец успешно введен.");
                        printf("\nОбычный вектор столбец:\n");
                        print_usual_matrix(&vector_column);
                    
                        printf("Разряженный вектор-стобец:");
                        print_special_vector(&sp_vector_column);
                    }
                }
                
                break;
            case MULTIPLICATION_MATRIX_BY_VECTOR:
                break;
            case MULTIPLICATION_MATRIX:
                // mult_matrix(&matrix1, &matrix2);
                break;
            case PERF_EVALUATION:
                break;
        }

        print_main_menu();
        printf("Выберите пункт из меню: ");

    }
    if (matrix.matrix != NULL)
        free_matrix(matrix.matrix, matrix.n);

    return EXIT_SUCCESS;
}
