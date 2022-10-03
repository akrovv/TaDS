#ifndef __SORTS_H__
#define __SORTS_H__

void selection_sort_by_fields(travel_t countries[], size_t len);
void selection_sort_by_keys(key_travel_t keys[], size_t len);
int merge_sort_by_fields(travel_t countries[], size_t l, size_t r);
int merge_sort_by_keys(key_travel_t keys[], size_t l, size_t r);
void merge_keys(key_travel_t keys[], size_t l, size_t middle, size_t r);
void merge_fields(travel_t countries[], size_t l, size_t middle, size_t r);
void buble_sort_flag_table(travel_t *countries, size_t n_countries);
void buble_sort_flag_key(key_travel_t *key, size_t n_key);
void insert_sort_table(travel_t *countries, size_t n_countries);
void insert_sort_key(key_travel_t *key, size_t n_key);

#endif
