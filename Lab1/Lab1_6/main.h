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

double function_a(double x);

double function_b(double x);

double function_c(double x);

double function_d(double x);

enum Errors trapezoidal_rule(const double epsilon, double (*f)(double), double* result);

#endif