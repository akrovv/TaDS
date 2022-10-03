#ifndef __DATA_H__
#define __DATA_H__

#define LEN 300

int add_country(travel_t *countries, size_t *n_countries);
int delete_country_by_name(travel_t countries[], char str[], size_t *len);
int delete_country_by_materic(travel_t countries[], char str[], size_t *len);
int delete_country_by_population(travel_t countries[], long int population, size_t *len);
int delete_country_by_capital(travel_t countries[], char str[], size_t *len);
int delete_country_by_test(travel_t countries[], bool test, size_t *len);
int delete_country_by_number_objects(travel_t countries[], unsigned int number_objects, size_t *len);
int delete_country_by_name_object(travel_t countries[], char str[], size_t *len);
int delete_country_by_main_season(travel_t countries[], unsigned short main_season, size_t *len);
int delete_country_by_air_temperature(travel_t countries[], short air_temperature, size_t *len);
int delete_country_by_water_temperature(travel_t countries[], short water_temperature, size_t *len);
int delete_country_by_time_flying(travel_t countries[], unsigned short time_flying, size_t *len);
int delete_country_by_kind_sport(travel_t countries[], char str[], size_t *len);
int delete_country_by_min_count_price(travel_t countries[], unsigned long int min_count_price, size_t *len);
int find_country_by_sport(travel_t countries[], size_t len, char materic[], char sport[]);

#endif
