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

enum Errors swap_min_max(short** arr, const int size);

enum Errors fill_array(short** result_array, const int size_of_array, const short a, const short b);

enum Errors generate_array_with_find_closest(short * array_a, const int size_of_array_a,
                                            short * array_b, const int size_of_array_b,
                                            short ** array_c);

#endif