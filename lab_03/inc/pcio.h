#ifndef __PCIO_H__
#define __PCIO_H__

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int read_special_matrix_element(int **matrix, size_t n, size_t m, int non_zero_el);
int read_non_zero_elements(int *count, size_t n, size_t m);
int read_special_matrix(usual_matrix_t *matrix);
int create_matrix(int ***matrix, size_t n, size_t m);
int allocate_matrix(int ***matrix, size_t n, size_t m);
void free_matrix(int **matrix, size_t n);
int read_special_vector_column(usual_matrix_t *matrix);
int read_special_vector_column_element(int **matrix, size_t n, int non_zero_el);
void auto_fill_matrix(usual_matrix_t *matrix);
void print_special_matrix(const special_matrix_t *matrix);
void print_special_vector(special_vector_column_t *matrix);
int create_special_vector(special_vector_column_t *special_vector, usual_matrix_t *matrix);
int create_special_matrix(special_matrix_t *special_vector, usual_matrix_t *matrix);
size_t get_zero_element(int **matrix, size_t n, size_t m);
int allocate_special_matrix(special_matrix_t *special_matrix);
int allocate_special_vector(special_vector_column_t *special_vector);
void free_special_matrix(special_matrix_t *special_matrix);
void free_special_vector(special_vector_column_t *special_vector);
void auto_fill(usual_matrix_t *matrix, int non_zero_el);

// Print
void print_usual_matrix(usual_matrix_t *matrix);
void print_matrix_menu(void);
void print_main_menu(void);
void print_vector_menu(void);

#endif 
