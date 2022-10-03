#include "utils.h"
#include "check.h"

bool is_situated_digit_value(char str[])
{
    for (size_t i = 0; str[i] != '\0'; i++)
        if (isdigit(str[i]))
            return true;
    return false;
}

bool is_digit_string(char str[])
{
    for (size_t i = 0; str[i] != '\0'; i++)
        if (!isdigit(str[i]))
            return false;
    return true;
}

bool is_correct_materic(char str[])
{
    char materics [NUMBER_MATERIC][STRING_MATERIC]  = {"Европа",
                                                       "Азия",
                                                       "Северная Америка",
                                                       "Южная Америка",
                                                       "Океания",
                                                       "Африка"};

    for (size_t i = 0; i < NUMBER_MATERIC; i++)
        if (strcmp(materics[i], str) == 0)
            return true;
    return false;
}

bool is_incorrect_symb(char str[])
{
    size_t i = 0;
    i++;

    for (; str[i] != '\0'; i++)
        if (str[i] == ' ')
            return true;

    return false;
}

bool is_correct_type_sightseeing(char str[])
{
    char name_object[NUMBER_SIGHSEENG * 3][STRING_OBJECTS] = {"природа", "история", "искусство", "Природа", "История", "Искусство"};
    for (size_t i = 0; i <  NUMBER_SIGHSEENG * 3; i++)
        if (strcmp(name_object[i], str) == 0)
            return true;

    return false;
}

bool is_correct_type_sport(char str[])
{
    char kind_sport[KIND_SPORT * 3][STRING_SPORT] = {"горные лыжи", "серфинг", "восхождения", "Горные лыжи", "Серфинг", "Восхождения"};
    for (size_t i = 0; i <  NUMBER_SIGHSEENG * 2; i++)
        if (strcmp(kind_sport[i], str) == 0)
            return true;

    return false;
}

bool is_previous(travel_t countries[], travel_t *country, size_t len)
{
    for (size_t i = 0; i < len; i++)
        if (!strcmp(countries[i].main_data_t.name_country, country->main_data_t.name_country))
            return true;
    return false;
}

