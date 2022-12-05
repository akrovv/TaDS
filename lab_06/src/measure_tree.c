#include "measure.h"
#include "read.h"
#include "operations.h"
#include <sys/time.h>

static int get_quantity_by_letter_file(char letter, FILE *f)
{
    int quantity = 0;
    rewind(f);

    while (!feof(f))
    {
        char str[SIZE];
        fgets(str, SIZE, f);
        if (str[strlen(str) - 1] == '\n')
            str[strlen(str) - 1] = '\0';

        if (str[0] == letter)
            quantity++;
    }

    return quantity;
}

static void print_table_result(char letter, long long int time)
{
    printf("+-------+------------+\n");
    printf("| %6s | %6s |\n", "Буква", "Время (мс)");
    printf("+-------+------------+\n");
    printf("| %5c |  %9lld | \n", letter, time);
    printf("+-------+------------+\n");
}

void measure_find(void)
{
    struct timeval tv_start, tv_stop;
    int64_t time_u = 0, time_s = 0;
    char file_names[I_STEP][SIZE] = { "data_measure/measure_search1.txt", "data_measure/measure_search2.txt", 
    "data_measure/measure_search3.txt", "data_measure/measure_search4.txt", "data_measure/measure_search5.txt"};


    for (int i = 0, j = 50; i < I_STEP; i++)
    {
        FILE *f = fopen(file_names[i], "r");
        binary_tree_t binary_tree;
        binary_tree.head = NULL;

        (void) file_read(&binary_tree, f);

        if (j == 2000)
            j *= 5;

        printf("Время поиска для %d\n", j);

        printf("Для бинарного дерева поиска:\n");

        for (int i = 0; i <= I_STEP; i++)
        {
            int letter = 97 + rand() % (122 - 97 + 1);
            gettimeofday(&tv_start, NULL);
            get_quantity_by_letter(binary_tree.head, letter);
            gettimeofday(&tv_stop, NULL);
            time_u = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
            print_table_result(letter, time_u);
        }


        printf("----------------------------\n");
        printf("Для обычного поиска в файле:\n");
        printf("----------------------------\n");
        
        for (int i = 0; i <= I_STEP; i++)
        {
            int letter = 97 + rand() % (122 - 97 + 1);
            gettimeofday(&tv_start, NULL);
            (void) get_quantity_by_letter_file(letter, f);
            gettimeofday(&tv_stop, NULL);
            time_u = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
            print_table_result(letter, time_u);
        }
        

        if (j < 100) 
            j += 450;
        else 
            j += 500;

        time_u = 0, time_s = 0;

        fclose(f);
    }

}

