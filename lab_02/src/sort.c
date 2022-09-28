#include "utils.h"
#include "sorts.h"

void selection_sort_by_fields(travel_t countries[], size_t len)
{
    for (size_t i = 0; i < len - 1; i++)
    {
        size_t min = i;

        for (size_t j = i + 1; j < len; j++)
            if (countries[min].main_data_t.population > countries[j].main_data_t.population) 
                min = j;
        
        if (min != i)
        {
            travel_t tmp = countries[i];
            countries[i] = countries[min];
            countries[min] = tmp;
        }
    }
}

void selection_sort_by_keys(key_travel_t keys[], size_t len)
{
    for (size_t i = 0; i < len - 1; i++)
    {
        size_t min = i;

        for (size_t j = i + 1; j < len; j++)
            if (keys[min].population > keys[j].population) 
                min = j;
        
        if (min != i)
        {
            key_travel_t tmp = keys[i];
            keys[i] = keys[min];
            keys[min] = tmp;
        }
    }
}

void merge_sort_by_fields(travel_t countries[], size_t len) // не работает :(
{
    size_t middle = len / 2;

    if (middle % 2)
        middle++;
    size_t h = 1;
    size_t step;
    travel_t *c = malloc(sizeof(travel_t) * len);


    while (h < len) 
    {
        step = h;
        size_t i = 0;
        size_t j = middle;
        size_t k = 0; 
        while (step <= middle) 
        {
            while ((i < step) && (j < len) && (j < (middle + step))) 
            {
                if (countries[i].main_data_t.population < countries[j].main_data_t.population)  
                {
                    c[k] = countries[i];
                    i++; 
                    k++;
                }
                else 
                {
                    c[k] = countries[j];
                    j++; 
                    k++;
                }
            }
            while (i < step) 
            {
                c[k] = countries[i];
                i++;
                k++;
            }
            while ((j < (middle + step)) && (j < len)) 
            {
                c[k] = countries[j];
                j++; 
                k++;
            }
            step = step + h;
        }

        h = h * 2;

        for (i = 0; i < len; i++)
            countries[i] = c[i];
    }

    free(c);

}

