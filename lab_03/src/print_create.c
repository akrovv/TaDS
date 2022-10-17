#include "pcio.h"

void free_matrix(int **matrix, size_t n)
{
    for (size_t i = 0; i < n; i++)
        free(matrix[i]);

    free(matrix);
}
void free_special_matrix(special_matrix_t *special_matrix)
{
    free(special_matrix->A);
    free(special_matrix->JA);
    free(special_matrix->IA.list);
}
void free_special_vector(special_vector_column_t *special_vector)
{
    free(special_vector->A);
    free(special_vector->IA.list);
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

void auto_fill_matrix(usual_matrix_t *matrix)
{
    allocate_matrix(&matrix->matrix, matrix->n, matrix->m);

    for (size_t i = 0; i < matrix->n; i++)
        for (size_t j = 0; j < matrix->m; j++)
            matrix->matrix[i][j] = rand() % 100;
}

int create_matrix(int ***matrix, size_t n, size_t m)
{
    allocate_matrix(matrix, n, m);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
        {
            int el;

            if (scanf("%d", &el) != 1)
            {
                free_matrix(*matrix, n);
                return 1;
            }

            *(*(*matrix + i) + j) = el;
        }

    return 0;
}

void print_usual_matrix(usual_matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->n; i++)
    {
        for (size_t j = 0; j < matrix->m; j++)
            printf("%d ", matrix->matrix[i][j]);
        printf("\n");
    }
}

int read_special_matrix(usual_matrix_t *matrix)
{
    int rc = 1;
    int non_zero_el = 0;
    while (rc != 0)
    {
        rc = read_non_zero_elements(&non_zero_el, matrix->n, matrix->m);
        printf("%d\n", rc);
        if (rc == EXIT_SUCCESS)
        {
            rc = allocate_matrix(&matrix->matrix, matrix->n, matrix->m);
            if (rc == EXIT_SUCCESS)
                read_special_matrix_element(matrix->matrix, matrix->n, matrix->m, non_zero_el);
        } else
            printf("Ошибка! Количество введено не верно!");
    }

    return rc;
}

int read_non_zero_elements(int *count, size_t n, size_t m)
{
    int rc = EXIT_SUCCESS;
    int non_zero_el = 0;
    char buff[8];
    printf("Введите количество ненулевых элементов (от 0 до %lu): ", n * m);
    if (scanf("%d", &non_zero_el) != 1) 
    {
        fgets(buff, sizeof(buff), stdin);
        return 1;
    }
    else if (non_zero_el < 0 || non_zero_el > n * m)
        return 1;
    else
        *count = non_zero_el;
    return rc;
}

int read_special_matrix_element(int **matrix, size_t n, size_t m, int non_zero_el)
{
    printf("\nВведите ненулевой элемент (элемент, i, j):\n");
    for (int i = 0, ii = 0, jj = 0, el = 0; i < non_zero_el;)
    {
        if (scanf("%d%d%d", &el, &ii, &jj) != 3)
            return 1;
        else if (ii < 0 || jj < 0 || ii > n - 1 || jj > m - 1)
            return 1;
        else if (el == 0)
            return 1;
        else
        {
            if (matrix[ii][jj] == 0)
            {
                matrix[ii][jj] = el;
                i++;
            }
            else
                return 1;
        }
    }
    return 0;
}

int read_special_vector_column(usual_matrix_t *matrix)
{
    int rc = 1;
    int non_zero_el = 0;

    while (rc != 0)
    {
        matrix->m = 1;
        rc = read_non_zero_elements(&non_zero_el, matrix->n, matrix->m);
        if (rc == EXIT_SUCCESS)
        {
            rc = allocate_matrix(&matrix->matrix, matrix->n, matrix->m);
            if (rc == EXIT_SUCCESS)
                read_special_vector_column_element(matrix->matrix, matrix->n, non_zero_el);
        } 
        else
            printf("Ошибка! Количество введено не верно!");
    }

    return rc;
}

int read_special_vector_column_element(int **matrix, size_t n, int non_zero_el)
{
    printf("\nВведите ненулевой элемент (элемент, i):\n");
    for (int i = 0, ii = 0, el = 0; i < non_zero_el;)
    {
        if (scanf("%d%d", &el, &ii) != 2)
            return 1;
        else if (ii < 0 || ii > n - 1)
            return 1;
        else if (el == 0)
            return 1;
        else
        {
            if (matrix[ii][0] == 0)
            {
                matrix[ii][0] = el;
                i++;
            }
            else
                return 1;
        }
    }

    return 0;
}

int create_special_matrix(special_matrix_t *special_matrix, usual_matrix_t *matrix)
{
    int rc = EXIT_SUCCESS;
    if (matrix->n < MIN_N || matrix->n > MAX_N)
        return 1;
    else if (matrix->m < MIN_M || matrix->m > MAX_M)
        return 1;
    else
    {
        special_matrix->n = matrix->n;
        special_matrix->m = matrix->m;
        int non_zero_el = get_zero_element(matrix->matrix, matrix->n, matrix->m);
        special_matrix->na = non_zero_el;
        rc = allocate_special_matrix(special_matrix);
        if (rc == EXIT_SUCCESS)
        {
            special_matrix->IA.list[0] = 0;
            for (int i = 0, curr_a = 0, curr_ia = 1; i < matrix->n; i++) {
                for (int j = 0; j < matrix->m; j++)
                {
                    if (matrix->matrix[i][j] != 0) {
                        special_matrix->A[curr_a] = matrix->matrix[i][j];
                        special_matrix->JA[curr_a] = j;
                        curr_a++;
                    }
                }
                special_matrix->IA.list[curr_ia] = curr_a;
                curr_ia++;
            }
            special_matrix->IA.list[special_matrix->n] = special_matrix->na;
        }
    }
    return rc;
}

int create_special_vector(special_vector_column_t *special_vector, usual_matrix_t *matrix)
{
    int rc = EXIT_SUCCESS;
    if (matrix->n < MIN_N || matrix->n > MAX_N)
        return 1;
    else
    {
        special_vector->n = matrix->n;
        int non_zero_el = get_zero_element(matrix->matrix, matrix->n, matrix->m);
        special_vector->na = non_zero_el;
        rc = allocate_special_vector(special_vector);
        if (rc == EXIT_SUCCESS)
        {
            special_vector->IA.list[0] = 0;
            for (int i = 0, curr_a = 0, curr_ia = 1; i < matrix->n; i++) {
                if (matrix->matrix[i][0] != 0)
                {
                    special_vector->A[curr_a] = matrix->matrix[i][0];
                    curr_a++;
                }
                special_vector->IA.list[curr_ia] = curr_a;
                curr_ia++;
            }
        }
    }
    return rc;
}

int allocate_special_matrix(special_matrix_t *special_matrix)
{
    special_matrix->A = malloc(special_matrix->na * sizeof(int));
    if (special_matrix->A == NULL)
        return 1;
    special_matrix->JA = malloc(special_matrix->na * sizeof(int));
    if (special_matrix->JA == NULL)
    {
        free(special_matrix->A);
        special_matrix->A = NULL;
        return 1;
    }
    special_matrix->IA.list = malloc((special_matrix->n + 1) * sizeof(int));
    if (special_matrix->IA.list == NULL)
    {
        free(special_matrix->A);
        special_matrix->A = NULL;
        free(special_matrix->JA);
        special_matrix->JA = NULL;
        return 1;
    }
    return EXIT_SUCCESS;
}
int allocate_special_vector(special_vector_column_t *special_vector)
{
    special_vector->A = malloc(special_vector->na * sizeof(int));
    if (special_vector->A == NULL)
        return 1;
    special_vector->IA.list = malloc((special_vector->n + 1) * sizeof(int));
    if (special_vector->IA.list == NULL)
    {
        free(special_vector->A);
        special_vector->A = NULL;
        return 1;
    }
    return EXIT_SUCCESS;
}

size_t get_zero_element(int **matrix, size_t n, size_t m)
{
    size_t count = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (matrix[i][j] != 0)
                count++;
    return count;
}

// Print

void print_main_menu(void)
{
    printf("\n--------------Меню--------------\n"
           "1 - Ввести матрицу\n"
           "2 - Ввести вектор-стоблец\n"
           "3 - Умножить матрицу на вектор\n"
           "4 - Вывести матрицы и вектор\n"
           "5 - Замерить эффективность\n"
           "0 - Выход\n");
}

void print_matrix_menu(void)
{
    printf("\n"
           "1 - Ввести матрицу в обычном ввиду\n"
           "2 - Ввести матрицу в разреженном ввиде\n"
           "3 - Автозаполение матрицы\n");
}
void print_vector_menu(void)
{
    printf("\n"
           "1 - Ввести вектор в обычном ввиду\n"
           "2 - Ввести вектор в разреженном ввиде\n"
           "3 - Автозаполение вектора\n");
}

void print_special_matrix(const special_matrix_t *matrix)
{
    printf("\n A = [");
    for (int i = 0; i < matrix->na; i++)
        printf(" %d", matrix->A[i]);
    printf(" ]\n");
    printf("JA = [");
    for (int i = 0; i < matrix->na; i++)
        printf(" %d", matrix->JA[i]);
    printf(" ]\n");
    printf("IA = [");
    for (int i = 0; i < matrix->n + 1; i++)
        printf(" %d", matrix->IA.list[i]);
    printf(" ]\n");
}
void print_special_vector(special_vector_column_t *matrix)
{
    printf("\n A = [");
    for (int i = 0; i < matrix->na; i++)
        printf(" %d", matrix->A[i]);
    printf(" ]\n");
    printf("JA = [ ]\n");
    printf("IA = [");
    for (int i = 0; i < matrix->n + 1; i++)
        printf(" %d", matrix->IA.list[i]);
    printf(" ]\n");
}
