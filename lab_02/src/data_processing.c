#include "utils.h"
#include "read_print.h"
#include "data.h"
#include "errors.h"
#include "check.h"

int add_country(travel_t *countries, size_t *n_countries)
{
    size_t i = *n_countries;
    int rc = EXIT_SUCCESS, rc_scanf = 0;
    char buffers[8];
    fgets(buffers, 8, stdin);
    printf("\nВведите название страны (не должно содержать цифры): ");
    fgets(countries[i].main_data_t.name_country, STRING_COUNTRY + 2, stdin);
    if (strlen(countries[i].main_data_t.name_country) > STRING_COUNTRY)
        rc = COUNTRY_OVERFLOW;
    else
    {

        if (countries[i].main_data_t.name_country[strlen(countries[i].main_data_t.name_country) - 1] == '\n')
            countries[i].main_data_t.name_country[strlen(countries[i].main_data_t.name_country) - 1] = '\0';
        if (is_situated_digit_value(countries[i].main_data_t.name_country))
            rc = COUNTRY_DIGIT_ERR;
        else
        {
            printf("Введите название столицы (не дожно содержать цифры): ");
            fgets(countries[i].main_data_t.capital, STRING_CAPITAL + 2, stdin);
            if (strlen(countries[i].main_data_t.capital) > STRING_CAPITAL)
                rc = CAPITAL_OVERFLOW;
            else
            {
                if (countries[i].main_data_t.capital[strlen(countries[i].main_data_t.capital) - 1] == '\n')
                    countries[i].main_data_t.capital[strlen(countries[i].main_data_t.capital) - 1] = '\0';
                if (is_situated_digit_value(countries[i].main_data_t.capital))
                    rc = COUNTRY_DIGIT_ERR;
                else
                {
                    printf(" - Материков всего 6 и название вводятся строго по названию\n"
                           "Европа, Азия, Северная или Южная Америка, Африка, Океания\n");
                    printf("Введите материк: ");
                    fgets(countries[i].main_data_t.materic, STRING_MATERIC + 2, stdin);
                    if (strlen(countries[i].main_data_t.materic) > STRING_MATERIC)
                        rc = MATERIC_OVERFLOW;
                    else
                    {
                        if (countries[i].main_data_t.materic[strlen(countries[i].main_data_t.materic) - 1] == '\n')
                            countries[i].main_data_t.materic[strlen(countries[i].main_data_t.materic) - 1] = '\0';
                        if (is_situated_digit_value(countries[i].main_data_t.materic))
                            rc = MATERIC_DIGIT_ERR;
                        else
                        {
                            printf("Введите количество жителей: ");
                            rc_scanf = scanf("%ld", &countries[i].main_data_t.population);
                            if (countries[i].main_data_t.population <= 0 || rc_scanf == 0)
                                rc = POPULATION_ZERO_ERROR;
                            else
                            {
                                long buff = 0;
                                printf("\nСтрана требует прививку/ПЦР?\n");
                                printf("<1> - Да или 0 - нет\n");
                                printf("Введите значение: ");
                                rc_scanf = scanf("%ld", &buff);
                                if (rc_scanf == 0)
                                    return EXIT_FAILURE;
                                if (buff == 0)
                                    countries[i].covid_tests = false;
                                else
                                    countries[i].covid_tests = true;

                                printf ("\nВыберите вид туризма\n"
                                        "1 - Экскурсионный\n"
                                        "2 - Пляжный\n"
                                        "3 - Спортивный\n"
                                        "Если >3 или <1 то в данных будут не заполнены (пропущены)\n"
                                        "Введите значение вида туризма: ");
                                rc_scanf = scanf("%ld", &buff);
                                if (rc_scanf == 0)
                                    return EXIT_FAILURE;

                                if (buff == 1)
                                {
                                    countries[i].tourism.tourism_sightseeing = true;
                                    printf(" - Введите количество объектов: ");
                                    rc_scanf =scanf("%ld", &buff);
                                    if (buff > 0)
                                        countries[i].tourism.kid_tourism.sightseeing.number_objects = buff;
                                    if (buff <= 0)
                                        rc = NUMBER_OBJECTS_IS_NEGATIVE;
                                    else if (rc_scanf == 0)
                                        rc = NOT_DIGIT_NUMBER_OBJECTS;
                                    else
                                    {
                                        printf(" - Введите тематику (строго одно из трех - (1)История, (2)Природа, (3)Культура): ");
                                        rc_scanf =scanf("%ld", &buff);
                                        if (buff == 1)
                                            strcpy(countries[i].tourism.kid_tourism.sightseeing.name_object, "История");
                                        else if (buff == 2)
                                            strcpy(countries[i].tourism.kid_tourism.sightseeing.name_object, "Природа");
                                        else if (buff == 3)
                                            strcpy(countries[i].tourism.kid_tourism.sightseeing.name_object, "Культура");
                                        else
                                            rc = EXIT_SUCCESS;
                                    }
                                }
                                else if (buff == 2)
                                {
                                    countries[i].tourism.tourism_beach = true;
                                    printf("\nЗначение для ввода\n"
                                           "1 - Весна\n"
                                           "2 - Лето\n"
                                           "3 - Осень\n"
                                           "4 - Зима\n"
                                           "5 - Все сезоны\n"
                                           "Другое значение - Нейзвестно\n"
                                           "Введите значение: ");
                                    scanf("%ld", &buff);
                                    if (buff > 5 || buff < 1)
                                        countries[i].tourism.kid_tourism.beach.main_season = 0;
                                    else
                                        countries[i].tourism.kid_tourism.beach.main_season = buff;
                                    printf("Введите температуру воздуха: ");
                                    rc_scanf = scanf("%hd", &countries[i].tourism.kid_tourism.beach.air_temperature);
                                    if (rc_scanf == 0)
                                        return TESTS_VALUE_ERR;
                                    printf("Введите температуру воды: ");
                                    rc_scanf = scanf("%hd", &countries[i].tourism.kid_tourism.beach.water_temperature);
                                    if (rc_scanf == 0)
                                        return TESTS_VALUE_ERR;
                                    printf("Введите время полета до страны (1 - 24 ч.): ");
                                    rc_scanf = scanf("%hu", &countries[i].tourism.kid_tourism.beach.time_flying);
                                    if (countries[i].tourism.kid_tourism.beach.time_flying <= 0 ||
                                        countries[i].tourism.kid_tourism.beach.time_flying > 24)
                                        rc = TIME_FLYING_IS_NEG;
                                    else if (rc_scanf == 0)
                                        rc = NOT_DIGIT_TIME_FLYING;
                                }
                                else if (buff == 3)
                                {
                                    countries[i].tourism.tourism_sport = true;
                                    printf("\nЗначение для ввода\n"
                                           "1 - Дайвинг\n"
                                           "2 - Серфинг\n"
                                           "3 - Горные лыжи\n"
                                           "4 - Восхождение\n");
                                    printf("Введите вид спорта: ");
                                    rc_scanf = scanf("%ld", &buff);
                                    if (buff == 1)
                                        strcpy(countries[i].tourism.kid_tourism.sport.kind_sport, "дайвинг");
                                    else if (buff == 2)
                                        strcpy(countries[i].tourism.kid_tourism.sport.kind_sport, "серфинг");
                                    else if (buff == 3)
                                        strcpy(countries[i].tourism.kid_tourism.sport.kind_sport, "горные лыжи");
                                    else if (buff == 4)
                                        strcpy(countries[i].tourism.kid_tourism.sport.kind_sport, "восхождение");
                                    else
                                        return EXIT_FAILURE;
                                    printf("Введите стоимость: ");
                                    rc_scanf = scanf("%ld", &buff);
                                    if (buff > 0 && rc_scanf)
                                        countries[i].tourism.kid_tourism.sport.min_count_price = (long unsigned) buff;
                                    else
                                        rc = MIN_COUNT_PRICE_IS_NEG;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (rc == EXIT_SUCCESS)
        *n_countries = i + 1;
    return rc;
}

int delete_country_by_name(travel_t countries[], char str[], size_t *len)
{
    bool is_find = false;

    for (size_t i = 0; i < *len; i++)
        if (!strcmp(countries[i].main_data_t.name_country, str))
        {
            for (size_t j = i; j < *len - 1; j++)
                countries[j] = countries[j + 1];

            is_find = true;
            (*len)--;
            i--;
        }

    if (!is_find)
        return NOT_FIND;

    return EXIT_SUCCESS;
}

int delete_country_by_materic(travel_t countries[], char str[], size_t *len)
{
    bool is_find = false;

    for (size_t i = 0; i < *len; i++)
        if (!strcmp(countries[i].main_data_t.materic, str))
        {
            for (size_t j = i; j < *len - 1; j++)
                countries[j] = countries[j + 1];

            is_find = true;
            (*len)--;
            i--;
        }

    if (!is_find)
        return NOT_FIND;

    return EXIT_SUCCESS;
}

int delete_country_by_population(travel_t countries[], long int population, size_t *len)
{
    bool is_find = false;

    for (size_t i = 0; i < *len; i++)
        if (countries[i].main_data_t.population ==  population)
        {
            for (size_t j = i; j < *len - 1; j++)
                countries[j] = countries[j + 1];

            is_find = true;
            (*len)--;
            i--;
        }

    if (!is_find)
        return NOT_FIND;

    return EXIT_SUCCESS;
}

int delete_country_by_capital(travel_t countries[], char str[], size_t *len)
{
    bool is_find = false;

    for (size_t i = 0; i < *len; i++)
        if (!strcmp(countries[i].main_data_t.capital, str))
        {
            for (size_t j = i; j < *len - 1; j++)
                countries[j] = countries[j + 1];

            is_find = true;
            (*len)--;
            i--;
        }

    if (!is_find)
        return NOT_FIND;

    return EXIT_SUCCESS;
}

int delete_country_by_test(travel_t countries[], bool test, size_t *len)
{
    bool is_find = false;

    for (size_t i = 0; i < *len; i++)
        if (countries[i].covid_tests == test)
        {
            for (size_t j = i; j < *len - 1; j++)
                countries[j] = countries[j + 1];

            is_find = true;
            (*len)--;
            i--;
        }

    if (!is_find)
        return NOT_FIND;

    return EXIT_SUCCESS;
}

int delete_country_by_number_objects(travel_t countries[], unsigned int number_objects, size_t *len)
{
    bool is_find = false;

    for (size_t i = 0; i < *len; i++)
        if (countries[i].tourism.tourism_sightseeing && countries[i].tourism.kid_tourism.sightseeing.number_objects ==  number_objects)
        {
            for (size_t j = i; j < *len - 1; j++)
                countries[j] = countries[j + 1];

            is_find = true;
            (*len)--;
            i--;
        }

    if (!is_find)
        return NOT_FIND;

    return EXIT_SUCCESS;
}

int delete_country_by_name_object(travel_t countries[], char str[], size_t *len)
{
    bool is_find = false;

    for (size_t i = 0; i < *len; i++)
        if (countries[i].tourism.tourism_sightseeing && !strcmp(countries[i].tourism.kid_tourism.sightseeing.name_object, str))
        {
            for (size_t j = i; j < *len - 1; j++)
                countries[j] = countries[j + 1];

            is_find = true;
            (*len)--;
            i--;
        }

    if (!is_find)
        return NOT_FIND;

    return EXIT_SUCCESS;
}

int delete_country_by_main_season(travel_t countries[], unsigned short main_season, size_t *len)
{
    bool is_find = false;

    for (size_t i = 0; i < *len; i++)
        if (countries[i].tourism.tourism_beach && countries[i].tourism.kid_tourism.beach.main_season ==  main_season)
        {
            for (size_t j = i; j < *len - 1; j++)
                countries[j] = countries[j + 1];

            is_find = true;
            (*len)--;
            i--;
        }

    if (!is_find)
        return NOT_FIND;

    return EXIT_SUCCESS;
}

int delete_country_by_air_temperature(travel_t countries[], short air_temperature, size_t *len)
{
    bool is_find = false;

    for (size_t i = 0; i < *len; i++)
        if (countries[i].tourism.tourism_beach && countries[i].tourism.kid_tourism.beach.air_temperature == air_temperature)
        {
            for (size_t j = i; j < *len - 1; j++)
                countries[j] = countries[j + 1];

            is_find = true;
            (*len)--;
            i--;
        }

    if (!is_find)
        return NOT_FIND;

    return EXIT_SUCCESS;
}

int delete_country_by_water_temperature(travel_t countries[], short water_temperature, size_t *len)
{
    bool is_find = false;

    for (size_t i = 0; i < *len; i++)
        if (countries[i].tourism.tourism_beach && countries[i].tourism.kid_tourism.beach.water_temperature ==  water_temperature)
        {
            for (size_t j = i; j < *len - 1; j++)
                countries[j] = countries[j + 1];

            is_find = true;
            (*len)--;
            i--;
        }

    if (!is_find)
        return NOT_FIND;

    return EXIT_SUCCESS;
}

int delete_country_by_time_flying(travel_t countries[], unsigned short time_flying, size_t *len)
{
    bool is_find = false;

    for (size_t i = 0; i < *len; i++)
        if (countries[i].tourism.tourism_beach && countries[i].tourism.kid_tourism.beach.time_flying ==  time_flying)
        {
            for (size_t j = i; j < *len - 1; j++)
                countries[j] = countries[j + 1];

            is_find = true;
            (*len)--;
            i--;
        }

    if (!is_find)
        return NOT_FIND;

    return EXIT_SUCCESS;
}

int delete_country_by_kind_sport(travel_t countries[], char str[], size_t *len)
{
    bool is_find = false;

    for (size_t i = 0; i < *len; i++)
        if (countries[i].tourism.tourism_sport && !strcmp(countries[i].tourism.kid_tourism.sport.kind_sport, str))
        {
            for (size_t j = i; j < *len - 1; j++)
                countries[j] = countries[j + 1];

            is_find = true;
            (*len)--;
            i--;
        }

    if (!is_find)
        return NOT_FIND;

    return EXIT_SUCCESS;
}

int delete_country_by_min_count_price(travel_t countries[], unsigned long int min_count_price, size_t *len)
{
    bool is_find = false;

    for (size_t i = 0; i < *len; i++)
        if (countries[i].tourism.tourism_sport && countries[i].tourism.kid_tourism.sport.min_count_price ==  min_count_price)
        {
            for (size_t j = i; j < *len - 1; j++)
                countries[j] = countries[j + 1];

            is_find = true;
            (*len)--;
            i--;
        }

    if (!is_find)
        return NOT_FIND;

    return EXIT_SUCCESS;
}


int find_country_by_sport(travel_t countries[], size_t len, char materic[], char sport[])
{
    int is_find = 0;
    for (size_t i = 0; i < len; i++)
        if (countries[i].tourism.tourism_sport)
            if (!strcmp(countries[i].main_data_t.materic, materic) && !strcmp(countries[i].tourism.kid_tourism.sport.kind_sport, sport))
            {
                print_basic_info(&countries[i]);
                print_travel_sport(&countries[i].tourism.kid_tourism.sport);
                printf("---------------------------------------------\n");
                is_find = 1;
            }

    return is_find;
}
