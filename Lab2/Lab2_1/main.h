#ifndef MAIN_H_FLAG
#define MAIN_H_FLAG

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>
#include <time.h>

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    ERROR_OPEN_FILE,
};

enum Errors is_valid_flag(const char *str);

enum Errors my_strlen(const char *str, int* result);

enum Errors my_reversed(const char *str, char** result);

enum Errors my_capitalize(const char *str, char **result);

enum Errors my_nedo_sort(const char *str, char **result);

enum Errors convert_str_to_int(const char *str, long long int * result, int base);

enum Errors my_concotenation(char **str, char **result, int count_str, long long int seed);


#endif