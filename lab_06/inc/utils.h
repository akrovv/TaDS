#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define _GNU_SOURCE

#define BUFF_SIZE 8

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
