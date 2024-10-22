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
#include <string.h>

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    ERROR_OPEN_FILE,
};

enum Errors is_valid_flag(const char *str);

enum Errors is_convex_polygon(int* result, const int count, ...);

enum Errors evaluate_polynomial(double *result, double x, int count, ...);

enum Errors find_kaprekar_numbers(int* result, int base, int count, ...);

#endif