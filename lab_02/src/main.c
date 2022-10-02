#include "utils.h"
#include "sorts.h"
#include "read_print.h"
#include "data.h"
#include "time.h"
#include "errors.h"
#include "check.h"

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

    if ((rc = read_array_travel_country(f, countries, &len)))
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
                    
                    if(!(rc = delete_country_by_name(countries, str, &len)))
                        print_table(countries, len);
                    else
                        printf("Такой страны нет!\n");
                }
                else
                    printf("Данные пусты!\n");
                break;
            case PRINT_SORTED_TABLE_BY_KEY:
                if (len)
                {
                    fill_keys_array(keys, countries, len);
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
            case FIND_COUNTRY:
                if (len)
                {
                    char materics[NUMBER_MATERIC][STRING_MATERIC] = { "Европа",
                                                                          "Азия",
                                                                          "Африка",
                                                                          "Южная Америка",
                                                                          "Северная Америка",
                                                                          "Океания"};
                    printf("0 - Европа\n"
                               "1 - Азия\n"
                               "2 - Африка\n"
                               "3 - Южная Америка\n"
                               "4 - Северная Америка\n"
                               "5 - Океания\n");
                    printf("Выберите материк: ");

                    char buff[8];

                    size_t find_option;
                    if (scanf("%zu", &find_option) == 1 && (find_option >= 0 && find_option <= 5))
                    {
                        char sport[STRING_SPORT + 1];
                        fgets(buff, 8, stdin);
                        printf("Введите название вида спорта: ");
                        if (fgets(sport, STRING_SPORT + 1, stdin) != NULL && strlen(sport) < STRING_SPORT)
                        {
                            if (sport[strlen(sport) - 1] == '\n')
                                    sport[strlen(sport) - 1] = '\0';
                            if (is_situated_digit_value(sport))
                                ;
                            if (!find_country_by_sport(countries, len, materics[find_option], sport))
                                printf("Ни одной страны не было найдено!\n");
                        }
                        else
                            rc = (strlen(sport) >= STRING_SPORT) ? STRING_SPORT_OVERFLOW : SCAN_ERROR;         
                    }
                    else 
                        rc = SCAN_ERROR;
                }
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
