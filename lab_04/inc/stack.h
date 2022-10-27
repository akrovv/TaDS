#ifndef __STACK_H__
#define __STACK_H__

#include "utils.h"

int calc_expr(stack_array_t *stack, int *error, size_t count_num, size_t count_sign);
int push_array(stack_array_t *stack, char symb);
char pop_array(stack_array_t *stack);
int push_list(stack_list_t **stack, char symb);
char pop_list(stack_list_t **head);
int calc_expr_list(stack_list_t **stack, int *error, size_t count_num, size_t count_sign);

#endif
