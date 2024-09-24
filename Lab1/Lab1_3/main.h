#ifndef MAIN_H_FLAG
#define MAIN_H_FLAG

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
};

typedef struct {
    double real;
    double imag;
} Complex;

typedef struct {
    int col_vo_solutions; 
    double a,b,c;
    Complex solution1; 
    Complex solution2;
} QuadraticSolution;

enum Errors is_valid_flag(const char *str);

enum Errors convert_str_to_double(const char *str, double * result);

enum Errors convert_str_to_int(const char *str, long long int * result, const int base);

enum Errors enumeration_quadratic_equation_parameters(const double eps, const double* mas_nam, QuadraticSolution** result, int* col_vo_rez);

void print_quadratic_solution(const QuadraticSolution result);

enum Errors is_number_multiple(const long long int a, const long long int b, int* result);

enum Errors is_sides_triangle_possible(const double eps, const double sides[3], int* result);

#endif