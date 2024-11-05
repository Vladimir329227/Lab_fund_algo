#include "main.h"

enum Errors dichotomy_method(double (*f)(double), double a, double b, double epsilon, double* result) {
    if (epsilon <= 0 || fabs(b - a) < epsilon || result == NULL || f == NULL) 
        return INVALID_INPUT;

    if (f(a) * f(b) >= 0)
        return INVALID_INPUT;

    int current_iteration = 0;
    while (fabs(b - a) > epsilon) {
        current_iteration++;
        if (current_iteration > MAX_ITERATIONS)
            return INVALID_INPUT;
        *result = (a + b) / 2.0;
        if (f(a) * f(*result) < 0) 
            b = *result;
        else 
            a = *result;

        if (isnan(*result) || isinf(*result))
            return INVALID_INPUT;
    }
    *result = (a + b) / 2.0;
    if (isnan(*result) || isinf(*result))
            return INVALID_INPUT;
    return OK;
}