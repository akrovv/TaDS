#include "utils.h"
#include "sorts.h"
#include "read_print.h"
#include "data.h"
#include "time.h"
#include "errors.h"
#include "check.h"

int main(int argc, char **argv)
{
    if (argc < 2)
        return MAIN_PARAM_ERROR;
    
    FILE *f;

    f = fopen(argv[1], "r");
    int rc = EXIT_SUCCESS;

    if (f == NULL)
        rc = FILE_NOT_FOUND;

    travel_t countries[NUMBER_COUNTRY];
    key_travel_t keys[NUMBER_COUNTRY];

    size_t len = 0;

    if ((rc = read_array_travel_country(f, countries, &len)))
    {
        print_add_err(rc);
        return rc;
    }
    size_t option = 1;

    print_task();

    print_menu();

    printf("Выберите пункт из менню: ");
    while (scanf("%zu", &option) == 1 && option && !rc)
    {
        switch (option)
        {
            case ADD:
                if (len + 1 >= NUMBER_COUNTRY)
                    rc = STRUCT_OVERFLOW;
                else if (!(rc = add_country(countries, &len)))
                {
                    if (!is_previous(countries, &countries[len - 1], len - 1))
                    {
                        print_table(countries, len);
                        f = fopen(argv[1], "w+");
                        rewrite_data(f, countries, len);
                        fclose(f);
                        printf("Файл %s успешно изменен", argv[1]);
                    }
                    else
                        printf("Данная страна уже есть в таблице!\n");
                }
                else if (rc)
                    printf("Страна не была добавлена\n");
        
                break;
            case REMOVE_BY_FIELD:
                if (len)
                {
                    size_t option_del;
                    printf("0 - Название страны\n"
                               "1 - Материк\n"
                               "2 - Количество жителей\n"
                               "3 - Столица\n"
                               "4 - Прививка\n"
                               "5 - Количество объектов\n"
                               "6 - Основной вид\n"
                               "7 - Основной сезон\n"
                               "8 - Температура воздуха\n"
                               "9 - Температура воды\n"
                               "10 - Время полета до страны\n"
                               "11 - Вид спорта\n"
                               "12 - Минимальная стоимость отдыха\n");
                    printf("Выберите поле, по которому нужно удалить: ");
                    if (scanf("%zu", &option_del) != 1)
                        rc = SCAN_ERROR;
                    else
                    {
                        if (option_del == 0)
                        {
                            char str[STRING_COUNTRY + 1];
                            printf("Введите название страны: ");
                            if (fscanf(stdin, "%s", str) != 1 || strlen(str) >= STRING_COUNTRY)
                                rc = SCAN_ERROR;
                            else
                            {
                                if (str[strlen(str) - 1] == '\n')
                                    str[strlen(str) - 1] = '\0';
                                if(!(rc = delete_country_by_name(countries, str, &len)))
                                {
                                    if (len)
                                    {
                                        print_table(countries, len);
                                        f = fopen(argv[1], "w+");
                                        rewrite_data(f, countries, len);
                                        fclose(f);
                                        printf("Файл %s успешно изменен", argv[1]);
                                    }
                                    else
                                    {
                                        printf("Таблица пуста!\n");
                                        f = fopen(argv[1], "w");
                                        fclose(f);
                                    }
                                }
                            }
                        }
                        else if (option_del == 1)
                        {
                            char str[STRING_MATERIC + 1];
                            printf("Введите название материка (Европа, Азия, Африка, Южная Америка, Океания): ");
                            if (fscanf(stdin, "%s", str) != 1 || strlen(str) >= STRING_MATERIC)
                                rc = SCAN_ERROR;
                            if (str[strlen(str) - 1] == '\n')
                                str[strlen(str) - 1] = '\0';
                            if (!is_correct_materic(str))
                                rc = NOT_IS_MATERIC;
                            else 
                                if(!(rc = delete_country_by_materic(countries, str, &len)))
                                {
                                    if (len)
                                    {
                                        print_table(countries, len);
                                        f = fopen(argv[1], "w+");
                                        rewrite_data(f, countries, len);
                                        fclose(f);
                                        printf("Файл %s успешно изменен", argv[1]);
                                    }
                                    else
                                    {
                                        printf("Таблица пуста!\n");
                                        f = fopen(argv[1], "w");
                                        fclose(f);
                                    }
                                }
                        }
                        else if (option_del == 2)
                        {
                            long int population;
                            printf("Введите количество жителей: ");
                            if (scanf("%ld", &population) != 1)
                                rc = SCAN_ERROR;
                            else if (population <= 0)
                                rc = POPULATION_ZERO_ERROR;
                            else if(!(rc = delete_country_by_population(countries, population, &len)))
                            {
                                if (len)
                                {
                                    print_table(countries, len);
                                    f = fopen(argv[1], "w+");
                                    rewrite_data(f, countries, len);
                                    fclose(f);
                                    printf("Файл %s успешно изменен", argv[1]);
                                }
                                else
                                {
                                    printf("Таблица пуста!\n");
                                    f = fopen(argv[1], "w");
                                    fclose(f);
                                }
                            }
                        }
                        else if (option_del == 3)
                        {
                            char str[STRING_CAPITAL + 1];
                            printf("Введите название столицы: ");
                            if (fscanf(stdin, "%s", str) != 1 || strlen(str) >= STRING_CAPITAL)
                                rc = SCAN_ERROR;
                            else
                            {
                                if (str[strlen(str) - 1] == '\n')
                                    str[strlen(str) - 1] = '\0';
                                if(!(rc = delete_country_by_capital(countries, str, &len)))
                                {
                                    if (len)
                                    {
                                        print_table(countries, len);
                                        f = fopen(argv[1], "w+");
                                        rewrite_data(f, countries, len);
                                        fclose(f);
                                        printf("Файл %s успешно изменен", argv[1]);
                                    }
                                    else
                                    {
                                        printf("Таблица пуста!\n");
                                        f = fopen(argv[1], "w");
                                        fclose(f);
                                    }
                                }
                            }
                        }
                        else if (option_del == 4)
                        {
                            short test;
                            printf("Введите есть ли пцр или нет (0 или 1): ");
                            if (scanf("%hd", &test) != 1)
                                rc = SCAN_ERROR;
                            else if (test < 0 || test > 1)
                                rc = NOT_TEST;
                            else if (!(rc = delete_country_by_test(countries, test, &len)))
                            {
                                if (len)
                                {
                                    print_table(countries, len);
                                    f = fopen(argv[1], "w+");
                                    rewrite_data(f, countries, len);
                                    fclose(f);
                                    printf("Файл %s успешно изменен", argv[1]);
                                }
                                else
                                {
                                    printf("Таблица пуста!\n");
                                    f = fopen(argv[1], "w");
                                    fclose(f);
                                }
                            }
                        }
                        else if (option_del == 5)
                        {
                            unsigned int number_objects;
                            printf("Введите количество объектов: ");
                            if (scanf("%u", &number_objects) != 1)
                                rc = SCAN_ERROR;
                            else if (number_objects <= 0)
                                rc = NUMBER_OBJECTS_IS_NEGATIVE;
                            else if (!(rc = delete_country_by_number_objects(countries, number_objects, &len)))
                            {
                                if (len)
                                {
                                    print_table(countries, len);
                                    f = fopen(argv[1], "w+");
                                    rewrite_data(f, countries, len);
                                    fclose(f);
                                    printf("Файл %s успешно изменен", argv[1]);
                                }
                                else
                                {
                                    printf("Таблица пуста!\n");
                                    f = fopen(argv[1], "w");
                                    fclose(f);
                                }
                            }
                        }
                        else if (option_del == 6)
                        {
                            char name_object[STRING_OBJECTS];
                            printf("Введите основной вид (природа, история, искусство): ");
                            if (fscanf(stdin, "%s", name_object) != 1 || strlen(name_object) >= STRING_OBJECTS)
                                rc = SCAN_ERROR;
                            else 
                            {
                                if (name_object[strlen(name_object) - 1] == '\n')
                                    name_object[strlen(name_object) - 1] = '\0';
                                if (!is_correct_type_sightseeing(name_object))
                                    rc = ERROR_NAME_OBJECT;
                                else if (!(rc = delete_country_by_name_object(countries, name_object, &len)))
                                {
                                    if (len)
                                    {
                                        print_table(countries, len);
                                        f = fopen(argv[1], "w+");
                                        rewrite_data(f, countries, len);
                                        fclose(f);
                                        printf("Файл %s успешно изменен", argv[1]);
                                    }
                                    else
                                    {
                                        printf("Таблица пуста!\n");
                                        f = fopen(argv[1], "w");
                                        fclose(f);
                                    }
                                }
                            }
                        }
                        else if (option_del == 7)
                        {
                            unsigned short main_season;
                            printf("Введите основной сезон: ");
                            if (scanf("%hu", &main_season) != 1)
                                rc = SCAN_ERROR;
                            else if (main_season > 12)
                                rc = MAIN_SEASON_ERROR;
                            else if (!(rc = delete_country_by_main_season(countries, main_season, &len)))
                            {
                                if (len)
                                {
                                    print_table(countries, len);
                                    f = fopen(argv[1], "w+");
                                    rewrite_data(f, countries, len);
                                    fclose(f);
                                    printf("Файл %s успешно изменен", argv[1]);
                                }
                                else
                                {
                                    printf("Таблица пуста!\n");
                                    f = fopen(argv[1], "w");
                                    fclose(f);
                                }
                            }
                        }
                        else if (option_del == 8)
                        {
                            short air_temperature;
                            printf("Введите температуру воздуха: ");
                            if (scanf("%hd", &air_temperature) != 1)
                                rc = SCAN_ERROR;
                            else if (!(rc = delete_country_by_air_temperature(countries, air_temperature, &len)))
                            {
                                if (len)
                                {
                                    print_table(countries, len);
                                    f = fopen(argv[1], "w+");
                                    rewrite_data(f, countries, len);
                                    fclose(f);
                                    printf("Файл %s успешно изменен", argv[1]);
                                }
                                else
                                {
                                    printf("Таблица пуста!\n");
                                    f = fopen(argv[1], "w");
                                    fclose(f);
                                }
                            }
                        }
                        else if (option_del == 9)
                        {
                            short water_temperature;
                            printf("Введите температуру воды: ");
                            if (scanf("%hd", &water_temperature) != 1)
                                rc = SCAN_ERROR;
                            else if (!(rc = delete_country_by_water_temperature(countries, water_temperature, &len)))
                            {
                                if (len)
                                {
                                    print_table(countries, len);
                                    f = fopen(argv[1], "w+");
                                    rewrite_data(f, countries, len);
                                    fclose(f);
                                    printf("Файл %s успешно изменен", argv[1]);
                                }
                                else
                                {
                                    printf("Таблица пуста!\n");
                                    f = fopen(argv[1], "w");
                                    fclose(f);
                                }
                            }
                        }
                        else if (option_del == 10)
                        {
                            unsigned short time_flying;
                            printf("Введите время полета: ");
                            if (scanf("%hu", &time_flying) != 1)
                                rc = SCAN_ERROR;
                            else if (!(rc = delete_country_by_time_flying(countries, time_flying, &len)))
                            {
                                if (len)
                                {
                                    print_table(countries, len);
                                    f = fopen(argv[1], "w+");
                                    rewrite_data(f, countries, len);
                                    fclose(f);
                                    printf("Файл %s успешно изменен", argv[1]);
                                }
                                else
                                {
                                    printf("Таблица пуста!\n");
                                    f = fopen(argv[1], "w");
                                    fclose(f);
                                }
                            }
                        }
                        else if (option_del == 11)
                        {
                            char kind_sport[STRING_SPORT];
                            printf("Введите название спорта (горные лыжи, серфинг, восхождения): ");
                            if (fscanf(stdin, "%s", kind_sport) != 1 || strlen(kind_sport) >= STRING_SPORT)
                                rc = SCAN_ERROR;
                            else
                            {
                                if (kind_sport[strlen(kind_sport) - 1] == '\n')
                                    kind_sport[strlen(kind_sport) - 1] = '\0';
                                if (!is_correct_type_sport(kind_sport))
                                    rc = ERROR_TYPE_SPORT;
                                else if (!(rc =  delete_country_by_kind_sport(countries, kind_sport, &len)))
                                {
                                    if (len)
                                    {
                                        print_table(countries, len);
                                        f = fopen(argv[1], "w+");
                                        rewrite_data(f, countries, len);
                                        fclose(f);
                                        printf("Файл %s успешно изменен", argv[1]);
                                    }
                                    else
                                    {
                                        printf("Таблица пуста!\n");
                                        f = fopen(argv[1], "w");
                                        fclose(f);
                                    }
                                }
                            }
                           
                        }
                        else if (option_del == 12)
                        {
                            unsigned long int min_count_price;
                            printf("Введите минимальную стоимость отдыха: ");
                            if (scanf("%lu", &min_count_price) != 1)
                                rc = SCAN_ERROR;
                            else if (!(rc = delete_country_by_min_count_price(countries, min_count_price, &len)))
                            {
                                if (len)
                                {
                                    print_table(countries, len);
                                    f = fopen(argv[1], "w+");
                                    rewrite_data(f, countries, len);
                                    fclose(f);
                                    printf("Файл %s успешно изменен", argv[1]);
                                }
                                else
                                {
                                    printf("Таблица пуста!\n");
                                    f = fopen(argv[1], "w");
                                    fclose(f);
                                }
                            }
                        }
                        if (rc && rc == NOT_FIND)
                            printf("Страны с данным полем нет!\n");
                     
                    }
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
                                rc = SPORT_DIGIT_ERROR;
                            else
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
        if (rc != EXIT_SUCCESS && rc != NOT_FIND)
        {
            print_add_err(rc);
            return rc;
        }
        print_menu();
        printf("Выберите пункт из менню: ");
    }
    if (!option)
        return SCAN_ERROR;

    return rc;
}
