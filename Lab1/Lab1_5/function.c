#include "main.h"

enum Errors convert_str_to_double(const char *str, double * result)
{
    char *endptr;
    *result = strtod(str, &endptr);
    if (*result == HUGE_VAL || *result == -HUGE_VAL)
    {
        return INVALID_INPUT;
    } else if (*endptr != '\0') {
        return INVALID_INPUT;
    }
    
    return OK;
}

enum Errors example_a(const double x, const double epsilon, double* result) {
    if (result == NULL ||  fabs(x) > DBL_MAX / 2 || epsilon < 0)
        return INVALID_INPUT;
    *result = 1.0; 
    double term = 1.0;
    int n = 1;

    while (fabs(term) > epsilon) {
        term *= x / n; 
        *result += term;
        n++;
    }

    return OK;
}

enum Errors example_b(const double x, const double epsilon, double* result) {
    if (result == NULL ||  fabs(x) > sqrt(DBL_MAX) || epsilon < 0)
        return INVALID_INPUT;
    *result = 1.0; 
    double term = 1.0;
    int n = 1;

    while (fabs(term) > epsilon) {
        term *= (-1) * pow(x, 2) / ((2 * n - 1) * (2 * n)); 
        *result += term; 
        n++;
    }

    return OK;
}

enum Errors example_с(const double x, const double epsilon, double* result) {
    if (result == NULL ||  fabs(x) > sqrt(DBL_MAX) || epsilon < 0)
        return INVALID_INPUT;
    *result = 0.0; 
    double term = 1.0;
    int n = 1;

    while (fabs(term) > epsilon) {
        term *= (3.0 * pow(n, 2) * pow(x, 2)) / (9.0 * pow(n, 2) - 9.0 * n + 2.0);
        *result += term;
        n++;
        if (n >= pow(10, 7))
            return INVALID_INPUT;
    }
    printf("OLL OK");
    return OK;
}

enum Errors example_d(const double x, const double epsilon, double* result) {
    if (result == NULL ||  fabs(x) > sqrt(DBL_MAX) || epsilon < 0)
        return INVALID_INPUT;
    *result = 0.0; 
    double term = 1.0;
    int n = 1;

    while (fabs(term) > epsilon) {
        term *= (-1) * pow(x, 2) / (4 * pow(n, 2) + 4 * n + 2);
        *result += term;
        n++;
        if (n >= pow(10, 7))
            return INVALID_INPUT;
    }

    return OK;
}