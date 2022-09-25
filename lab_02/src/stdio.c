#include "utils.h"

#define BUFF_SIZE 1000

int split_str_by_rule(char str[], travel_t *country)
{
    bool flag_name = false;
    bool flag_capital = false;
    bool flag_materic = false;
    char *s = strtok(str, ';');

    while (s != NULL)
    {
        if (!flag_name && strlen(s) < STRING_COUNTRY)
            flag_name = true;
        else if (!flag_capital && strlen(s) < STRING_CAPITAL)
            flag_capital = true;
        else if (!flag_materic && strlen(s) < STRING_MATERIC)
            flag_materic = true;
        else 
        {
            
        }


        s = strtok(s, ';');
    }
}

int read_str(FILE *f, travel_t *country, int(*split)(char str[], travel_t *country))
{
    char buffer[BUFF_SIZE + 1];

    if (fgets(buffer, BUFF_SIZE, f) == NULL)
        return 1;

    size_t len = strlen(buffer);
    
    if (buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';

    if (len > BUFF_SIZE || len == 0)
        return 1;

    split(buffer);

    return EXIT_SUCCESS;
}

int read_array_travel_country(FILE *f, travel_t countries[], size_t *size_countries)
{
    size_t i = 0;
    while (feof(f))
    {
        travel_t cur;
        if (read_str(f, &cur, &split_str_by_rule))
            return 1;
        i++;
    }

    *size_countries = i;

    return EXIT_SUCCESS;
}