#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MIN_N 1
#define MAX_N 5000
#define MIN_M MIN_N
#define MAX_M MAX_N

typedef enum { INPUT_MATRIX = 1, INPUT_VECTOR, MULTIPLICATION_MATRIX_BY_VECTOR, MULTIPLICATION_MATRIX, PERF_EVALUATION } menu_t;

typedef struct
{
    size_t n;
    size_t m;

    int **matrix;
} usual_matrix_t;

typedef struct st_list
{
    int *list;
} list_t;

typedef struct
{
    int n;
    int m;
    int na;

    int *A;
    int *JA;
    list_t IA;
} special_matrix_t;

typedef struct
{
    int n;
    int na;

    int *A;
    list_t IA;
} special_vector_column_t;

#endif
