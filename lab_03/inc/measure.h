#ifndef __MEASURE_H__
#define __MEASURE_H__

#include <sys/time.h>
#include "utils.h"
#include <math.h>

#define I_STEP 100
#define STEP_PERCENT 10

size_t get_size_matrix_t(usual_matrix_t *matrix);
size_t get_size_sp_matrix_t(special_matrix_t *matrix);
size_t get_size_sp_vector_t(special_vector_column_t *vector);
void default_matrix_t(usual_matrix_t *matrix);
void default_special_matrix_t(special_matrix_t *sp_matrix);
void default_special_vector_t(special_vector_column_t *sp_vector);
int perf_eval(void);
void print_measure(size_t size_m, size_t size_r, int64_t time_m, int64_t time_r, int percent);

#endif
