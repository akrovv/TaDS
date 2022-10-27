#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

#define SIZE_STACK 1001
#define BUFF_SIZE 8

typedef enum { ADD = 1, RM, CALC } option_t;

typedef struct
{
    char *string;
    size_t size_stack;
} stack_array_t;

typedef struct stack_list_t
{
    char symb;
    size_t size_stack;
    struct stack_list_t *next;
} stack_list_t;

#endif
