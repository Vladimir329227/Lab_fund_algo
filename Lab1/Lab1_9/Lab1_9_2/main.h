#ifndef MAIN_H_FLAG
#define MAIN_H_FLAG

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    ERROR_OPEN_FILE,
};

enum Errors convert_str_to_int(const char *str, long int * result, const int base);

enum Errors swap_min_max(long int** arr, int size);

enum Errors fill_array(long int** result_array, int size_of_array, long int a, long int b);

enum Errors generate_array_with_find_closest(long int * array_a, int size_of_array_a,
                                            long int * array_b, int size_of_array_b,
                                            long int ** array_c);

#endif