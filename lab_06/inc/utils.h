#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define _GNU_SOURCE

#define BUFF_SIZE 8

#define SCANF_ERROR 1
#define OUT_OF_RANGE 2
#define EXTRA_LETTERS 3
#define FIND_MENU 4
#define PRINT_MENU 5

typedef struct branch
{
    char *word;
    struct branch *parent;
    struct branch *left;
    struct branch *right;
} branch_t;

typedef struct binary_tree
{
    struct branch *head;
    size_t size;
} binary_tree_t;

#endif
