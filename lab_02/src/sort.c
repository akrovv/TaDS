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

void merge_fields(travel_t countries[], size_t l, size_t middle, size_t r)
{
    size_t i, j, k;
    size_t n1 = middle - l + 1;
    size_t n2 = r - middle;

    travel_t *left = malloc(sizeof(travel_t) * n1);
    travel_t *right = malloc(sizeof(travel_t) * n2);
 
    for (i = 0; i < n1; i++)
        left[i] = countries[l + i];
    for (j = 0; j < n2; j++)
        right[j] = countries[middle + 1 + j];
 
    i = 0;
    j = 0;
    k = l;
    
    while (i < n1 && j < n2) 
    {
        if (left[i].main_data_t.population <= right[j].main_data_t.population) 
            countries[k] = left[i++];
        else
            countries[k] = right[j++];
        k++;
    }
 
    while (i < n1) 
        countries[k++] = left[i++];
 
    while (j < n2)
        countries[k++] = right[j++];

    free(left);
    free(right);
}

void merge_keys(key_travel_t keys[], size_t l, size_t middle, size_t r)
{
    size_t i, j, k;
    size_t n1 = middle - l + 1;
    size_t n2 = r - middle;

    key_travel_t *left = malloc(sizeof(key_travel_t) * n1);
    key_travel_t *right = malloc(sizeof(key_travel_t) * n2);
 
    for (i = 0; i < n1; i++)
        left[i] = keys[l + i];
    for (j = 0; j < n2; j++)
        right[j] = keys[middle + 1 + j];
 
    i = 0;
    j = 0;
    k = l;
    
    while (i < n1 && j < n2) 
    {
        if (left[i].population <= right[j].population) 
            keys[k] = left[i++];
        else
            keys[k] = right[j++];
        k++;
    }
 
    while (i < n1) 
        keys[k++] = left[i++];
 
    while (j < n2)
        keys[k++] = right[j++];

    free(left);
    free(right);
}


int merge_sort_by_fields(travel_t countries[], size_t l, size_t r)
{
    if (l >= r)
        return EXIT_FAILURE;
    size_t middle = l + (r - l) / 2;

    merge_sort_by_fields(countries, l, middle);
    merge_sort_by_fields(countries, middle + 1, r);
 
    merge_fields(countries, l, middle, r);

    return EXIT_SUCCESS;
}

int merge_sort_by_keys(key_travel_t keys[], size_t l, size_t r)
{
    if (l >= r)
        return EXIT_FAILURE;
    size_t middle = l + (r - l) / 2;

    merge_sort_by_keys(keys, l, middle);
    merge_sort_by_keys(keys, middle + 1, r);
 
    merge_keys(keys, l, middle, r);

    return EXIT_SUCCESS;
}
