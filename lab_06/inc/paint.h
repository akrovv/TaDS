#ifndef __PAINT_H__
#define __PAINT_H__

#include "utils.h"

#define BST 1
#define HIGHLIGHT 2

typedef void (*action_t)(void *node, void *arg);

void treeExportToDot(FILE *f, const char *tree_name, void *tree, int flag, char letter);
static void inTreeColored(branch_t *tree, void (*color) (void *, void *, char), void *arg, char letter);
static void nodeToDotColored(void *node, void *param, char letter);
static void nodeToDot(void *node, void *param);
static void inTreeLook(branch_t *tree, action_t visit, void *arg);

#endif
