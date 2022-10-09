#include "utils.h"
#include "pcio.h"
#include "mult.h"

int main(void)
{

    int menu;
    print_menu();
    printf("Выберите пункт из меню: ");

    int **matrix1 = NULL;
    int **matrix2 = NULL;

    size_t n, m;
    size_t n1, m1;

    while (scanf("%d", &menu) == 1 && menu)
    {
        
        switch (menu)
        {
            
            case INPUT_MATRIX:
                printf("Размеры матрицы 1\n");
                printf("Введите количество строк матрицы 1:       ");
                scanf("%zu", &n);
                printf("Введите количество столбцов матрицы 1:    ");
                scanf("%zu", &m);
                create_matrix(&matrix1, n, m);
                printf("-------------------------------------\n");
                printf("Размеры матрицы 2\n");
                printf("Введите количество строк матрицы 2:       ");
                if (scanf("%zu", &n1) != 1)
                    return 1;
                printf("Введите количество столбцов матрицы 2:    ");
                if (scanf("%zu", &m1) != 1)
                    return 1;
                create_matrix(&matrix2, n1, m1);
                print_matrix(matrix1, n, m);
                print_matrix(matrix2, n1, m1);
                break;
            case MULTIPLICATION_MATRIX_BY_VECTOR:
                break;
            case MULTIPLICATION_MATRIX:
                mult_matrix(matrix1, n, m, matrix2, n1, m1);
                break;
            case PERF_EVALUATION:
                break;
        }

        print_menu();
        printf("Выберите пункт из меню: ");

    }
    free_matrix(matrix1, n);
    free_matrix(matrix2, n1);
    

    return EXIT_SUCCESS;
}
