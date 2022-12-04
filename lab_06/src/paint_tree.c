#include "paint.h"

static int cnt = 0;
static int i = 0;

static void inTreeLook(branch_t *tree, action_t visit, void *arg)
{
    i++;
    if (tree == NULL)
        return;

    inTreeLook(tree->left, visit, arg);
    visit(tree, arg);
    inTreeLook(tree->right, visit, arg);
}

static void inTreeColored(branch_t *tree, void (*color) (void *, void *, char), void *arg, char letter)
{
    i++;
    if (tree == NULL)
        return;

    inTreeColored(tree->left, color, arg, letter);
    color(tree, arg, letter);
    inTreeColored(tree->right, color, arg, letter);    
}

void treeExportToDot(FILE *f, const char *tree_name, void *tree, int flag, char letter)
{
    fprintf(f, "digraph %s {\n", tree_name);

    switch (flag) 
    {
        case BST:
            inTreeLook(tree, nodeToDot, f);
            break;
        case HIGHLIGHT:
            inTreeColored(tree, nodeToDotColored, f, letter);
    }
    fprintf(f, "}\n");
    cnt = 0;
}

static void nodeToDotColored(void *node, void *param, char letter)
{
    branch_t *node_n = node;

    FILE *out = param;

    if (node_n->word[0] == letter)
        fprintf(out, "%s [color=\"green\"]", node_n->word);

    if (node_n->left)
        fprintf(out, "%s -> %s;\n", node_n->word, node_n->left->word);
    else
    {
        fprintf(out, "null%d [shape=point];\n", cnt);
        fprintf(out, "%s -> null%d;\n", node_n->word, cnt++);
    }
    
    if (node_n->right)
    {
        fprintf(out, "%s -> %s;\n", node_n->word, node_n->right->word);
    }
    else
    {
        fprintf(out, "null%d [shape=point];\n", cnt);
        fprintf(out, "%s -> null%d;\n", node_n->word, cnt++);
    }
}

static void nodeToDot(void *node, void *param)
{
    branch_t *node_n = node;

    FILE *out = param;
    if (node_n->left)
        fprintf(out, "%s -> %s;\n", node_n->word, node_n->left->word);
    else
    {
        fprintf(out, "null%d [shape=point];\n", cnt);
        fprintf(out, "%s -> null%d;\n", node_n->word, cnt++);
    }
    
    if (node_n->right)
    {
        fprintf(out, "%s -> %s;\n", node_n->word, node_n->right->word);
    }
    else
    {
        fprintf(out, "null%d [shape=point];\n", cnt);
        fprintf(out, "%s -> null%d;\n", node_n->word, cnt++);
    }
    
}
