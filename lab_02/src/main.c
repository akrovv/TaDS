#include "utils.h"
#include "sorts.h"
#include "read_print.h"
#include "data.h"
#include "time.h"
#include "errors.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        return MAIN_PARAM_ERROR;
    
    FILE *f;

    f = fopen(argv[1], "r");

    if (f == NULL)
        return FILE_NOT_FOUND;

    travel_t countries[NUMBER_COUNTRY];
    key_travel_t keys[NUMBER_COUNTRY];

    size_t len = 0;
    int rc = EXIT_SUCCESS;

    if ((rc = read_array_travel_country(f, countries, &len, keys)))
    {
        print_add_err(rc);
        return rc;
    }

    size_t option = 1;

    print_menu();

    printf("Выберите пункт из менню: ");
    while (scanf("%zu", &option) == 1 && option)
    {
        switch (option)
        {
            case ADD:
                printf("Введите строку в форма: название страны;количество жителей;...;основной вид туризма:,...,\n");
                printf("Строка: ");
                if (!(rc = add_country(&countries[len])))
                {
                    len++;
                    print_table(countries, len);
                }
                else
                    printf("Страна не была добавлена\n");
        
                break;
            case REMOVE_BY_FIELD:
                if (len)
                {
                    char str[STRING_COUNTRY];
                    printf("Введите название страны, которую нужно удалить: ");
                    if (fscanf(stdin, "%s", str) != 1 || strlen(str) >= STRING_COUNTRY)
                        return 1;
                    
                    if (str[strlen(str) - 1] == '\n')
                        str[strlen(str) - 1] = '\0';
                    
                    if(!(rc = delete_country_by_name(countries, str, &len, keys)))
                        print_table(countries, len);;
                }
                else
                    printf("Данные пусты!\n");
                break;
            case PRINT_SORTED_TABLE_BY_KEY:
                if (len)
                {
                    merge_sort_by_keys(keys, 0, len - 1);
                    print_table_by_key(countries, keys, len);
                }
                else
                    printf("Данные пусты!\n");
                break;
            case PRINT_SORTED_TABLE_BY_FIELD:
                if (len)
                {
                    selection_sort_by_fields(countries, len);
                    print_table(countries, len);
                }
                else
                    printf("Данные пусты!\n");
                break;
            case PERF_EVALUATION:
                if (len)
                {
                    printf("Замеры времени:\n");
                    time_unsorted_arrays(countries, len, keys, len);
                }
                else
                    printf("Данные пусты!\n");
                break;
            case PRINT_TABLE:
                if (len)
                    print_table(countries, len);
                else
                    printf("Данные пусты!\n");
                break;
        }
        if (rc != EXIT_SUCCESS)
        {
            print_add_err(rc);
            return rc;
        }
        print_menu();
        printf("Выберите пункт из менню: ");
    }
    if (!option)
        return SCAN_ERROR;


    // selection_sort_by_field(countries, len);
    //selection_sort_by_keys(keys, len);

    // merge_sort_by_fields(countries, 0, len - 1);
    // merge_sort_by_keys(keys, 0, len - 1);


    return rc;
}
