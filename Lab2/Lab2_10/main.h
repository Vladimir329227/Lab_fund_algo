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

//enum Errors polynomial_rearrangement(double epsilon, double a, double **result, int degree, ...);
enum Errors polynomial_rearrangement(double a, double** result_coeffs, int degree, ...);

double evaluate_rearranged_polynomial(double* coeffs, int degree, double a, double x);

double evaluate_polynomial(double* coeffs, int degree, double a);

#endif