#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define STRING_OBJECTS 51
#define STRING_SPORT 51
#define STRING_COUNTRY 61
#define STRING_CAPITAL 41
#define STRING_MATERIC 37

#define NUMBER_COUNTRY 300
#define NUMBER_MATERIC 6
#define NUMBER_SIGHSEENG 3
#define KIND_SPORT 3

#define SIGHTSEEING_LEN 14

#define BASE_PARAMS 5
#define SIGHT_PARAMS 2
#define BEACH_PARAMS 4
#define SPORT_PARAMS 2

typedef enum
{
    ADD = 1,
    REMOVE_BY_FIELD,
    PRINT_SORTED_TABLE_BY_KEY,
    PRINT_SORTED_TABLE_BY_FIELD,
    PERF_EVALUATION,
    PRINT_TABLE
} optin_t;

typedef struct 
{
    unsigned int number_objects;
    char name_object[STRING_OBJECTS];
} sightseeing_t;

typedef struct
{
    unsigned short main_season;
    short air_temperature;
    short water_temperature;
    unsigned short time_flying;
} beach_t;

typedef struct
{
    char kind_sport[STRING_SPORT];
    unsigned long int min_count_price;
} sport_t;

typedef struct 
{
    bool tourism_sightseeing;
    bool tourism_beach;
    bool tourism_sport;
    union un_kid_toutism 
    {
        sightseeing_t sightseeing;
        beach_t beach;
        sport_t sport;
    } kid_tourism;
} tourism_t;

typedef struct
{
    struct main_data_country
    {
        char name_country[STRING_COUNTRY];
        char capital[STRING_CAPITAL];
        char materic[STRING_MATERIC];
        long int population;
    } main_data_t;
    bool covid_tests;
    tourism_t tourism;
} travel_t;

typedef struct 
{
    int index;
    long int population;
} key_travel_t;

#endif
