#ifndef MAIN_H_FLAG
#define MAIN_H_FLAG

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
};

enum Errors convert_str_to_double(const char *str, double * result);

enum Errors example_a(const double x,const double epsilon, double* result);

enum Errors example_b(const double x, const double epsilon, double* result);

enum Errors example_с(const double x, const double epsilon, double* result);

enum Errors example_d(const double x, const double epsilon, double* result);

#endif