#include "utils.h"
#include "errors.h"
#include "check.h"

#define BUFF_SIZE 1000
 
char *delete_spaces(char *str)
{
    char *res = malloc(strlen(str) * sizeof(char));
    size_t j = 0;
    size_t spaces = 0;
    for (size_t i = 0; str[i] != '\0'; i++)
    {
        if (i == spaces && str[i] == ' ')
            spaces++;
        else
        {
            if (isalpha(str[i]))
                res[j++] = str[i];
            if (i > 0 && isalpha(str[i - 1]) && str[i] == ' ')
                res[j++] = str[i];
        }
    }
    if (res[strlen(res) - 1] == ' ')
        res[strlen(res) - 1] = '\0';
    return res;
}

int split_str_by_rule(char str[], travel_t *country)
{   
    size_t i = 0;
    char *s = strtok(str, ";");
    char *type_travel;

    country->tourism.tourism_beach = false;
    country->tourism.tourism_sightseeing = false;
    country->tourism.tourism_sport = false;

    char *long_digit = NULL;

    while (s)
    {
        if (i == 0 && strlen(s) < STRING_COUNTRY)
        {
            if (is_situated_digit_value(s))
                return COUNTRY_DIGIT_ERR;
            if (is_incorrect_symb(s))
                return INCORRECT_COUNTRY_SYMB;
            i++;
            strcpy(country->main_data_t.name_country, s);
        }
        else if (i == 0 && strlen(s) >= STRING_COUNTRY)
            return COUNTRY_OVERFLOW;
        else if (i == 1 && strlen(s) < STRING_CAPITAL)
        {
            if (is_situated_digit_value(s))
                return CAPITAL_DIGIT_ERR;
            if (is_incorrect_symb(s))
                return INCORRECT_CAPITAL_SYMB;
            i++;
            strcpy(country->main_data_t.capital, s);
        }
        else if (i == 1 && strlen(s) >= STRING_CAPITAL)
            return CAPITAL_OVERFLOW;
        else if (i == 2 && strlen(s) < STRING_MATERIC)
        {
            if (is_situated_digit_value(s))
                return MATERIC_DIGIT_ERR;
            if (!is_correct_materic(s))
                return NOT_IS_MATERIC;
            i++;
            strcpy(country->main_data_t.materic, s);
        }
        else if (i == 2 && strlen(s) >= STRING_MATERIC)
            return MATERIC_OVERFLOW;
        else if (i == 3)
        {
            if (!is_digit_string(s))
                return NOT_DIGIT_POPULATION;
            long int population = strtol(s, &long_digit, 10);
            if (population <= 0)
                return POPULATION_ZERO_ERROR;
            i++;
            country->main_data_t.population = population;
        }
        else if (i == 4)
        {
            i++;
            if (strchr(s, '-') && strlen(s) == 1)
                country->covid_tests = false;
            else if (strchr(s, '+') && strlen(s) == 1)
                country->covid_tests =  true;
            else 
                return TESTS_VALUE_ERR;
        }
        else if (i == 5)
        {
            if (strstr(s, "Спортивный"))
                country->tourism.tourism_sport = true;
            else if (strstr(s, "Экскурсионный"))
                country->tourism.tourism_sightseeing = true;
            else if (strstr(s, "Пляжный"))
                country->tourism.tourism_beach = true;
            else
                return DATA_EMPTY_ERR;
        }
        else 
            return INCORRECT_STR;

        type_travel = s;
        s = strtok(NULL, ";");
    }
    
    if (i != BASE_PARAMS)
        return BASE_PARAMS_ERROR;

    if (strlen(type_travel) < SIGHTSEEING_LEN)
        return VAR_STRING_OVERFLOW;
    type_travel = (strstr(type_travel, ":")) + 1;
    i = 0;
    char *text = NULL;
    if (country->tourism.tourism_sightseeing)
    {
        type_travel = strtok(type_travel, ",");
        while (type_travel)
        {
            if (i == 0)
            {
                if (!is_digit_string(type_travel))
                    return NOT_DIGIT_NUMBER_OBJECTS;
                int number_objects = atoi(type_travel);
                if (number_objects <= 0)
                    return NUMBER_OBJECTS_IS_NEGATIVE;
                i++;
                country->tourism.kid_tourism.sightseeing.number_objects = number_objects;
            }
            else if (i == 1 && strlen(type_travel) < STRING_OBJECTS)
            {
                i++;
                if (!is_correct_type_sightseeing(type_travel))
                    return ERROR_NAME_OBJECT;
                    
                strcpy(country->tourism.kid_tourism.sightseeing.name_object, type_travel);   
            }
            else if (i == 1 && strlen(type_travel) >= STRING_OBJECTS)
                return NAME_OBJECT_OVERFLOW;
            else
                return INCORRECT_STR;

            type_travel = strtok(NULL, ",");
        }

        if (i < SIGHT_PARAMS)
            return SIGHT_PARAM_ERROR;
    }
    else if (country->tourism.tourism_beach)
    {
        int params;
        type_travel = strtok(type_travel, ",");
        while (type_travel)
        {
            if (i == 0)
            {
                if (!is_digit_string(type_travel))
                    return NOT_DIGIT_MAIN_SEASON;
                params = atoi(type_travel);
                if (params <= 0)
                    return MAIN_SEASON_IS_NEGATIVE;
                i++;
                country->tourism.kid_tourism.beach.main_season = params;
            }
            else if (i == 1)
            {
                if (!is_digit_string(type_travel))
                    return NOT_DIGIT_AIR_TEMP;
                params = atoi(type_travel);
                i++;
                country->tourism.kid_tourism.beach.air_temperature = params;  
            }
            else if (i == 2)
            {
                if (!is_digit_string(type_travel))
                    return NOT_DIGIT_WATER_TEMP;
                params = atoi(type_travel);

                if (params <= 0)
                    return WATER_TEMP_IS_NEG;
                i++;
                country->tourism.kid_tourism.beach.water_temperature = params; 
            }
            else if (i == 3)
            {
                if (!is_digit_string(type_travel))
                    return NOT_DIGIT_TIME_FLYING;
                params = atoi(type_travel);
        
                if (params <= 0)
                    return TIME_FLYING_IS_NEG;
                i++;
                country->tourism.kid_tourism.beach.time_flying = params; 
            }
            else
                return INCORRECT_STR;

            type_travel = strtok(NULL, ",");
        }
        if (i < BEACH_PARAMS)
            return BEACH_PARAM_ERROR;
    }
    else if (country->tourism.tourism_sport)
    {
        type_travel = strtok(type_travel, ",");
        while (type_travel)
        {
            if (i == 0 && strlen(type_travel) < STRING_SPORT)
            {
                i++;
                if (!is_correct_type_sport(type_travel))
                    return ERROR_TYPE_SPORT;
                strcpy(country->tourism.kid_tourism.sport.kind_sport, type_travel); 
            }
            else if (i == 0 && strlen(type_travel) >= STRING_SPORT)
                return STRING_SPORT_OVERFLOW;
            else if (i == 1)
            {
                if (!is_digit_string(type_travel))
                    return NOT_DIGIT_MIN_COUNT_PRICE;
                long int min_count_price = strtol(type_travel, &long_digit, 10);
                if (min_count_price < 0)
                    return MIN_COUNT_PRICE_IS_NEG;
                i++;
                country->tourism.kid_tourism.sport.min_count_price = min_count_price;
            }
            else
                return INCORRECT_STR;

            type_travel = strtok(NULL, ",");
        }

        if (i < SPORT_PARAMS)
            return SPORT_PARAM_ERROR;
    }
    else
        return INCORRECT_STR;

    free(text);

    return EXIT_SUCCESS;
}

int read_str(FILE *f, travel_t *country, int(*split)(char str[], travel_t *country))
{
    char buffer[BUFF_SIZE];

    if (fgets(buffer, BUFF_SIZE + 1, f) == NULL)
        return SCAN_ERROR;

    size_t len = strlen(buffer);
    
    if (buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';

    if (len > BUFF_SIZE || len == 0)
        return STRING_OVERFLOW;

    fscanf(f, "\n");

    return split(buffer, country);
}

int read_array_travel_country(FILE *f, travel_t countries[], size_t *size_countries)
{
    size_t i = 0;
    int rc = EXIT_SUCCESS;
    while (!feof(f))
    {
        travel_t cur;
        if ((rc = read_str(f, &cur, &split_str_by_rule)))
            return rc;
        countries[i] = cur;
        
        i++;
    }

    *size_countries = i;

    return rc;
}

void fill_keys_array(key_travel_t keys[], travel_t countries[], size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        keys[i].population = countries[i].main_data_t.population;
        keys[i].index = i;
    }
}

void print_basic_info(travel_t *country)
{
    printf("Название страны: %s\n", country->main_data_t.name_country);
    printf("Столица: %s\n", country->main_data_t.capital);
    printf("Материк: %s\n", country->main_data_t.materic);
    printf("Количество жителей: %ld\n", country->main_data_t.population);
}

void print_travel_sightseeing(sightseeing_t *country)
{
    printf("Количество объектов: %u\n", country->number_objects);
    printf("Основной вид: %s\n", country->name_object);
}

void print_travel_beach(beach_t *country)
{
    printf("Основной сезон: %hu\n", country->main_season);
    printf("Температура воздуха: %d°C\n", country->air_temperature);
    printf("Температура воды: %d°C\n", country->water_temperature);
    printf("Время полет: %huч\n", country->time_flying);
}

void print_travel_sport(sport_t *country)
{
    printf("Вид спорта: %s\n", country->kind_sport);
    printf("Минимальная стоимость отдыха: %lu руб.\n", country->min_count_price);
}

void print_table(travel_t countries[], size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        print_basic_info(&countries[i]);
        if (countries[i].tourism.tourism_sightseeing)
        {
            printf("Вид туризма: Экскурсионный\n");
            print_travel_sightseeing(&countries[i].tourism.kid_tourism.sightseeing);
        }
        else if (countries[i].tourism.tourism_beach)
        {
            printf("Вид туризма: Спортивный\n");
            print_travel_beach(&countries[i].tourism.kid_tourism.beach);
        }
        else if (countries[i].tourism.tourism_sport)
        {
            printf("Вид туризма: Пляжный\n");
            print_travel_sport(&countries[i].tourism.kid_tourism.sport);
        }
        printf("---------------------------------------------\n");
    }
}

void print_table_by_key(travel_t countries[], key_travel_t keys[], size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        print_basic_info(&countries[keys[i].index]);
        if (countries[keys[i].index].tourism.tourism_sightseeing)
        {
            printf("Вид туризма: Экскурсионный\n");
            print_travel_sightseeing(&countries[keys[i].index].tourism.kid_tourism.sightseeing);
        }
        else if (countries[keys[i].index].tourism.tourism_beach)
        {
            printf("Вид туризма: Спортивный\n");
            print_travel_beach(&countries[keys[i].index].tourism.kid_tourism.beach);
        }
        else if (countries[keys[i].index].tourism.tourism_sport)
        {
            printf("Вид туризма: Пляжный\n");
            print_travel_sport(&countries[keys[i].index].tourism.kid_tourism.sport);
        }
        printf("---------------------------------------------\n");
    }
}

void print_menu(void)
{
    printf("----------MENU---------                          ---------------Описание--------------\n"
           "1 - Добавить страну                              При добавление стран есть ряд ограничений:\n"
           "2 - Удалить страну                                 - Название стран не больше 30 символов\n"
           "3 - Отсортировать все страны (по ключу)            - Название столиц не больше 20 символов\n"
           "4 - Отсортировать все страны                       - Название материков(только Европа,\n"
           "5 - Оценка Эффетивности                              Северная или Южная Америка, Азия,\n"
           "6 - Вывести все страны                               Океания) ввод должен соотвествовать.\n"
           "0 - Выйти                                          - Название типов туризма только 3 вида\n"
           "                                                      Экскурсионный,Пляжный,Спортивный\n"
           "                                                   - Название для ввидов спортивного туризма\n"
           "                                                      не больше 40 элементов\n");
}
