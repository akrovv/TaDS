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

void buble_sort_flag_key(key_travel_t *key, size_t n_key)
{
    bool flag = true;
    key_travel_t buff;
    for (size_t i = 0; i < n_key; i++)
    {
        for (size_t j = i; j < n_key - 1; j++)
            if (key[j].population > key[j + 1].population)
            {
                buff = key[j];
                key[j] = key[j + 1];
                key[j + 1] = buff;
                flag = false;
            }
        if (flag)
            break;
    }
}
void buble_sort_flag_table(travel_t *countries, size_t n_countries)
{
    travel_t buff;
    bool flag = true;
    for (size_t i = 0; i < n_countries; i++)
    {
        for (size_t j = i; j < n_countries - 1; j++)
            if (countries[j].main_data_t.population > countries[j + 1].main_data_t.population)
            {
                buff = countries[j];
                countries[j] = countries[j + 1];
                countries[j + 1] = buff;
                flag = false;
            }
        if (flag)
            break;
    }
}

void insert_sort_table(travel_t *countries, size_t n_countries)
{
    for (size_t i = 1; i < n_countries; i++)
    {
        travel_t buff = countries[i];
        int j = i - 1;
        for (; j >= 0 && countries[j].main_data_t.population > buff.main_data_t.population; j--)
            countries[j + 1] = countries[j];
        countries[j + 1] = buff;
    }
}
void insert_sort_key(key_travel_t *key, size_t n_key)
{
    for (size_t i = 1; i < n_key; i++)
    {
        key_travel_t buff = key[i];
        int j = i - 1;
        for (; j >= 0 && key[j].population > buff.population; j--)
            key[j + 1] =key[j];
        key[j + 1] = buff;
    }
}
