#ifndef __TIME_H__
#define __TIME_H__

#include <sys/time.h>
#include <inttypes.h>
#include <ctype.h>

void make_table(void);
void make_data(int i, size_t size, size_t count_size_array, size_t one_element, int64_t time_1, int64_t time_2);
void my_cpy_st_travel(travel_t *arr_cp, travel_t *arr_src, size_t n, int repeat);
void my_cpy_st_key(key_travel_t *arr_cp, key_travel_t *arr_src, size_t n, int repeat);
void time_unsorted_arrays(travel_t *arr_с, size_t n_с, key_travel_t *arr_k, size_t n_k);

#endif
