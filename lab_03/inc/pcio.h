#ifndef __PCIO_H__
#define __PCIO_H__

#include <stdio.h>
#include <stdlib.h>

void print_menu(void);
int create_matrix(int ***matrix, size_t n, size_t m);
int allocate_matrix(int ***matrix, size_t n, size_t m);
void print_matrix(int **matrix, size_t n, size_t m);
void free_matrix(int **matrix, size_t n);

#endif 
