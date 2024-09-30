#include "main.h"

enum Errors convert_str_to_int(const char *str, long int * result, const int base)
{
    if (str == NULL || result == NULL)
        return INVALID_INPUT;
    char *endptr;
    *result = strtol(str, &endptr, base);

    if (*result == LONG_MAX || *result == LONG_MIN)
        return INVALID_INPUT;
    else if (*endptr != '\0') 
        return INVALID_INPUT;

    return OK;
}

enum Errors fill_array(long int** result_array, int size_of_array, long int a, long int b) {
    (*result_array) = (long int *) malloc(size_of_array * sizeof(long int));
    if (!(*result_array))
        return INVALID_MEMORY;

    for(int i = 0; i < size_of_array; ++i)
    {
        (*result_array)[i] = rand() % labs(b + 1 - a) + a;
    }
    return OK;
}

enum Errors swap_min_max(long int** arr, int size) {
    if (!arr || !(*arr) || size <= 1)
        return INVALID_INPUT;

    int minIdx = 0;
    int maxIdx = 0;

    for (int i = 1; i < size; i++) {
        if ((*arr)[i] < (*arr)[minIdx]) {
            minIdx = i;
        } else if ((*arr)[i] > (*arr)[maxIdx]) {
            maxIdx = i;
        }
    }

    long int temp = (*arr)[minIdx];
    (*arr)[minIdx] = (*arr)[maxIdx];
    (*arr)[maxIdx] = temp;
    return OK;
}

enum Errors find_closest(long int* arr, int size, int target, long int* result) {
    if (size == 0)
        return INVALID_INPUT; 

    *result  = arr[0];
    long int min_diff = abs(arr[0] - target);
    long int diff;
    for (int i = 1; i < size; i++) {
        diff = labs(arr[i] - target);
        if (diff < min_diff) {
            min_diff = diff;
            *result  = arr[i];
        }
    }

    return OK;
}

enum Errors generate_array_with_find_closest(long int * array_a, int size_of_array_a,
                                            long int * array_b, int size_of_array_b,
                                            long int ** array_c)
{
    if (!array_a || !array_b)
        return INVALID_INPUT;
    
    (*array_c) = (long int*) malloc(sizeof(long int) * size_of_array_a);
    if (!array_c)
        return INVALID_MEMORY;
    
    long int find_namber;
    for(int i = 0; i < size_of_array_a; ++i)
    {
        if (find_closest(array_b, size_of_array_b, array_a[i], &find_namber) != OK)
            return INVALID_INPUT;
        (*array_c)[i] = array_a[i] + find_namber;
    }

    return OK;
}


