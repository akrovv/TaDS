#ifndef __READ_PRINT_H__
#define __READ_PRINT_H__

char *delete_spaces(char *str);
int read_array_travel_country(FILE *f, travel_t countries[], size_t *size_countries, key_travel_t keys[]);
int split_str_by_rule(char str[], travel_t *country);
int read_str(FILE *f, travel_t *country, int(*split)(char str[], travel_t *country));
void print_table(travel_t countries[], size_t len);
void print_basic_info(travel_t *country);
void print_travel_sightseeing(sightseeing_t *country);
void print_travel_beach(beach_t *country);
void print_travel_sport(sport_t *country);
void print_menu(void);

#endif
