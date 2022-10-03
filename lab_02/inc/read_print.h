#ifndef __READ_PRINT_H__
#define __READ_PRINT_H__

char *delete_spaces(char *str);
int read_array_travel_country(FILE *f, travel_t countries[], size_t *size_countries);
int split_str_by_rule(char str[], travel_t *country);
int read_str(FILE *f, travel_t *country, int(*split)(char str[], travel_t *country));
void fill_keys_array(key_travel_t keys[], travel_t countries[], size_t len);
void print_table(travel_t countries[], size_t len);
void print_table_by_key(travel_t countries[], key_travel_t keys[], size_t len);
void print_basic_info(travel_t *country);
void print_travel_sightseeing(sightseeing_t *country);
void print_travel_beach(beach_t *country);
void print_travel_sport(sport_t *country);
void rewrite_data(FILE *f, travel_t *countries, size_t n_countries);
void print_menu(void);
void print_task(void);

#endif
