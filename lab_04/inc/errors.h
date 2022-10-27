#ifndef __ERROR_H__
#define __ERROR_H__

#include "utils.h"

#define STRING_CREATE_ERROR 1
#define INPUT_STACK_ERROR 2
#define INCORRECT_SYMB 3
#define SIZE_TOO_LONG 4
#define STACK_OVERFLOW 5
#define INCORRECT_EXPRESSION 6
#define PRINT_ERROR 7
#define SCANF_ERROR 8

void show_error(int error);

#endif
