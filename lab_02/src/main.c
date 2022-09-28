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

    // selection_sort_by_field(countries, len);
    //selection_sort_by_keys(keys, len);

    merge_sort_by_fields(countries, len);

    for (size_t i = 0; i < len; i++)
    {
        printf("%s %ld\n", countries[i].main_data_t.name_country, countries[i].main_data_t.population);
    }

    return EXIT_SUCCESS;
}
