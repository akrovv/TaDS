#ifndef __CHECK_H__
#define __CHECK_H__

#include <stdbool.h>
#include <ctype.h>

bool is_situated_digit_value(char str[]);
bool is_digit_string(char str[]);
bool is_correct_materic(char str[]);
bool is_incorrect_symb(char str[]);
bool is_correct_type_sightseeing(char str[]);
bool is_correct_type_sport(char str[]);
bool is_previous(travel_t countries[], travel_t *country, size_t len);

#endif
