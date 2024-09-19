#ifndef MAIN_H_FLAG
#define MAIN_H_FLAG

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

#define MAX_POW_TO_DALAY 7
#define PI 3.1415926535
#define EKS 2.71828182846


enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
};

enum Errors convert_str_to_double(const char *str, double * result);

enum Errors find_e_by_limit(double eps, double* rez);

enum Errors find_pi_by_limit(double eps, double* rez);

enum Errors find_ln_2_by_limit(double eps, double* rez);

enum Errors find_sqrt_2_by_limit(double eps, double* rez);

enum Errors find_gamma_by_limit(double eps, double* rez);

enum Errors find_e_by_row(double eps, double* rez);

enum Errors find_pi_by_row(double eps, double* rez);

enum Errors find_ln_2_by_row(double eps, double* rez);

enum Errors find_sqrt_2_by_row(double eps, double* rez);

enum Errors find_gamma_by_row(double eps, double* rez);

enum Errors find_e_by_equations(double eps, double* rez);

enum Errors find_pi_by_equations(double eps, double* rez);

enum Errors find_ln_2_equations(double eps, double* rez);

enum Errors find_sqrt_2_equations(double eps, double* rez);

enum Errors find_gamma_equations(double eps, double* rez);

#endif