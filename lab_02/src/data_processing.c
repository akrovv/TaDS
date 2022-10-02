#include "utils.h"
#include "read_print.h"
#include "data.h"
#include "errors.h"

int add_country(travel_t *countries)
{   
    char str[LEN + 1];

    if (fscanf(stdin, "%s", str) != 1 || strlen(str) >= LEN)
        return 1;

    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';

    return split_str_by_rule(str, countries);
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
            break;
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
                is_find = 1;
            }

    return is_find;
}
