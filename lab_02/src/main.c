#include "utils.h"
#include "sorts.h"
#include "read_print.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        return EXIT_FAILURE;
    
    FILE *f;

    f = fopen(argv[1], "r");

    if (f == NULL)
        return EXIT_FAILURE;

    travel_t countries[NUMBER_COUNTRY];
    key_travel_t keys[NUMBER_COUNTRY];

    size_t len = 0;

    if (read_array_travel_country(f, countries, &len, keys))
        return 1;

    size_t option;

    print_menu();

    if (scanf("%zu", &option) == 1 && option)
    {
        switch (option)
        {
            case ADD:
                break;
            case REMOVE_BY_FIELD:
                break;
            case PRINT_SORT_KEY:
                break;
            case PRINT_SORTED_TABLE_BY_FIELD:
                selection_sort_by_fields(countries, len);
                print_table(countries, len);
                break;
            case PRINT_SORTED_TABLE_BY_KEY:
                break;
        }
    }


    // selection_sort_by_field(countries, len);
    //selection_sort_by_keys(keys, len);

    // merge_sort_by_fields(countries, 0, len - 1);
    // merge_sort_by_keys(keys, 0, len - 1);


    return EXIT_SUCCESS;
}
