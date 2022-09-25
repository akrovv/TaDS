#include "utils.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        return EXIT_FAILURE;
    
    FILE *f;

    f = fopen(argv[1], 'r');

    if (f == NULL)
        return EXIT_FAILURE;





    return EXIT_SUCCESS;
}