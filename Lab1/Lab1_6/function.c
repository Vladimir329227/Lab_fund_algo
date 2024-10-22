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

double function_a(double x) {
    return log(1 + x) / x;
}

double function_b(double x) {
    return exp(-x*x/2);
}

double function_c(double x) {
    return log(1/(1 - x));
}

double function_d(double x) {
    return pow(x, x);
}

enum Errors trapezoidal_rule(const double epsilon, double (*f)(double), double* result) {
    if (result == NULL ||  *f == NULL || epsilon < 0)
        return INVALID_INPUT;
    int n = 1; 
    double b = 1.0, a = epsilon;
    double h = b - a; 
    double integral = 0.5 * h * (f(a) + f(b)); 
    *result = 0.0;
    double x0;
    do {
        n *= 2;
        h = (b - a) / n;
        *result = 0.0;

        for (double i = epsilon; i < n - epsilon; i++) {
            x0 = a + i * h;
            *result += h * f(x0);
        }

        if (fabs(*result - integral) < epsilon)
            break;

        integral = *result;

        if (n >= pow(10, 7))
            return INVALID_INPUT;
    } while (1);

    return OK;
}