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
#include <stdarg.h>

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    ERROR_OPEN_FILE,
};

enum Errors is_valid_flag(const char *str);

enum Errors convert_str_to_int(const char *str, long long int * result, int base);

enum Errors geometric_mean(double* result, int count, ...);

enum Errors fast_power(double base, int exponent, double* result);

#endif