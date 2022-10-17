#ifndef __MULT_H__
#define __MULT_H__

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int mult_matrix(usual_matrix_t *result, usual_matrix_t *matrix1, usual_matrix_t *matrix2);
int mult_special_matrix(special_vector_column_t *result, special_matrix_t *matrix, special_vector_column_t *vector);

#endif 
