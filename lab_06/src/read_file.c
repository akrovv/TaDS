#include "read.h"

static int str_read(binary_tree_t *binary_tree, FILE *f)
{
    size_t byte_len = 0;
    char *str = NULL;

    if (getline(&str, &byte_len, f) == -1)
       return EXIT_FAILURE;

    if (!str)
        return EXIT_FAILURE;

    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';

    insert(&binary_tree->head, str);

    return EXIT_SUCCESS;
}

int file_read(binary_tree_t *binary_tree)
{
    FILE *f = fopen("test.txt", "r");
    if (!f)
        return EXIT_FAILURE;

    int rc = EXIT_SUCCESS;

    while ((rc = str_read(binary_tree, f)) == EXIT_SUCCESS)
        ;

    return EXIT_SUCCESS;
}
