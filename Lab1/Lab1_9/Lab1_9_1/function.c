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

    srand(time(NULL));

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


