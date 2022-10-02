#include "check.h"
#include "utils.h"

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
    char name_object[NUMBER_SIGHSEENG][STRING_OBJECTS] = {"природа", "история", "искусство"};
    for (size_t i = 0; i <  NUMBER_SIGHSEENG; i++)
        if (strcmp(name_object[i], str) == 0)
            return true;

    return false;
}

bool is_correct_type_sport(char str[])
{
    char kind_sport[KIND_SPORT][STRING_SPORT] = {"горные лыжи", "серфинг", "восхождения"};
    for (size_t i = 0; i <  NUMBER_SIGHSEENG; i++)
        if (strcmp(kind_sport[i], str) == 0)
            return true;

    return false;
}

