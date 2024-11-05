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
#include <string.h>
#include <stdarg.h>

#define SIZE_INT 32

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    ERROR_OPEN_FILE,
};

typedef struct {
    int n;
    double *coords;
} Vector;

double norm_inf(Vector *v);
double norm_p(Vector *v, double p);
double norm_A(Vector *v, double *A, int n);

double norm_inf_wrapper(Vector *v, void *param);
double norm_p_wrapper(Vector *v, void *param);
double norm_A_wrapper(Vector *v, void *param);

enum Errors find_longest_vectors(double (*norm_func)(Vector *, void *), void *norm_param, int num_vectors, Vector ***longest_vectors, int *num_longest, ...);

#endif