#include "utils.h"
#include "read_print.h"
#include "data.h"

int add_country(travel_t *countries)
{   
    char str[LEN + 1];

    if (fscanf(stdin, "%s", str) != 1 || strlen(str) >= LEN)
        return 1;

    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';

    return split_str_by_rule(str, countries);
}

int delete_country_by_name(travel_t countries[], char str[], size_t *len, key_travel_t keys[])
{
    bool is_find = false;
    for (size_t i = 0; i < *len; i++)
        if (!strcmp(countries[keys[i].index].main_data_t.name_country, str))
        {
            for (size_t j = i; j < *len - 1; j++)
                keys[j] = keys[j + 1];

            is_find = true;
            break;
        }

    if (!is_find)
        return 1;

    for (size_t i = 0; i < *len; i++)
        if (!strcmp(countries[i].main_data_t.name_country, str))
        {
            for (size_t j = i; j < *len - 1; j++)
                countries[j] = countries[j + 1];

            (*len)--;
            break;
        }

    return EXIT_SUCCESS;
}
