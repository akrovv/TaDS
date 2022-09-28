#include "utils.h"

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

    while (s)
    {
        if (i == 0 && strlen(s) < STRING_COUNTRY)
        {
            i++;
            strcpy(country->main_data_t.name_country, s);
        }
        else if (i == 1 && strlen(s) < STRING_CAPITAL)
        {
            i++;
            strcpy(country->main_data_t.capital, s);
        }
        else if (i == 2 && strlen(s) < STRING_MATERIC)
        {
            i++;
            strcpy(country->main_data_t.materic, s);
        }
        else if (i == 3)
        {
            int population = atoi(s);
            if (!population)
                return 1;
            if (population < 0)
                return 1;
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
                return 1;
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
                return 1;

        }
        else 
            return 1;

        type_travel = s;
        s = strtok(NULL, ";");
    }
    if (strlen(type_travel) < SIGHTSEEING_LEN)
        return 1;
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
                int number_objects = atoi(type_travel);
                if (!number_objects)
                    return 1;
                if (number_objects < 0)
                    return 1;
                i++;
                country->tourism.kid_tourism.sightseeing.number_objects = number_objects;
            }
            else if (i == 1 && strlen(type_travel) < STRING_OBJECTS)
            {
                i++;
                text = delete_spaces(type_travel);
                strcpy(country->tourism.kid_tourism.sightseeing.name_object, text);   
            }
            else
                return 1;

            type_travel = strtok(NULL, ",");
        }

        if (i < SIGHT_PARAMS)
            return 1;
    }
    else if (country->tourism.tourism_beach)
    {
        int params;
        type_travel = strtok(type_travel, ",");
        while (type_travel)
        {
            if (i == 0)
            {
                params = atoi(type_travel);
                if (!params)
                    return 1;
                if (params < 0)
                    return 1;
                i++;
                country->tourism.kid_tourism.beach.main_season = params;
            }
            else if (i == 1)
            {
                params = atoi(type_travel);
                if (!params)
                    return 1;
                if (params < 0)
                    return 1;
                i++;
                country->tourism.kid_tourism.beach.air_temperature = params;  
            }
            else if (i == 2)
            {
                params = atoi(type_travel);
                if (!params)
                    return 1;
                if (params < 0)
                    return 1;
                i++;
                country->tourism.kid_tourism.beach.water_temperature = params; 
            }
            else if (i == 3)
            {
                params = atoi(type_travel);
                if (!params)
                    return 1;
                if (params < 0)
                    return 1;
                i++;
                country->tourism.kid_tourism.beach.time_flying = params; 
            }
            else
                return 1;

            type_travel = strtok(NULL, ",");
        }
        if (i < BEACH_PARAMS)
            return 1;
    }
    else if (country->tourism.tourism_sport)
    {
        type_travel = strtok(type_travel, ",");
        while (type_travel)
        {
            if (i == 0 && strlen(type_travel) < STRING_SPORT)
            {
                i++;
                text = delete_spaces(type_travel);
                strcpy(country->tourism.kid_tourism.sport.kind_sport, text); 
            }
            else if (i == 1)
            {
                int min_count_price = atoi(type_travel);
                if (!min_count_price)
                    return 1;
                if (min_count_price < 0)
                    return 1;
                i++;
                country->tourism.kid_tourism.sport.min_count_price = min_count_price;
            }
            else
                return 1;

            type_travel = strtok(NULL, ",");
        }

        if (i < SPORT_PARAMS)
            return 1;
    }
    else
        return 1;

    free(text);

    return EXIT_SUCCESS;
}

int read_str(FILE *f, travel_t *country, int(*split)(char str[], travel_t *country))
{
    char buffer[BUFF_SIZE];

    if (fgets(buffer, BUFF_SIZE + 1, f) == NULL)
        return 1;

    size_t len = strlen(buffer);
    
    if (buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';

    if (len > BUFF_SIZE || len == 0)
        return 1;

    fscanf(f, "\n");

    return split(buffer, country);
}

int read_array_travel_country(FILE *f, travel_t countries[], size_t *size_countries, key_travel_t keys[])
{
    size_t i = 0;
    while (!feof(f))
    {
        travel_t cur;
        if (read_str(f, &cur, &split_str_by_rule))
            return 1;
        countries[i] = cur;
        keys[i].population = cur.main_data_t.population;
        keys[i].index = i;
        
        i++;
    }

    *size_countries = i;

    return EXIT_SUCCESS;
}
