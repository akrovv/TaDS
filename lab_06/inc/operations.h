#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include "utils.h"

void insert(branch_t **head, char *value);
int deleteValue(branch_t *root, char *value);
size_t get_quantity_by_letter(branch_t *root, char value);
void print_tree(branch_t *head);
void sort(branch_t *head);
branch_t *getNodeByValue(branch_t *root, char *value);
void print_tree_file(FILE *f, branch_t *head);

#endif
