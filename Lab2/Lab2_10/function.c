#include "main.h"

void polynomial_derivative(double* coeffs, int degree, double* derivative_coeffs) {
    for (int i = 0; i < degree; i++) {
        derivative_coeffs[i] = coeffs[i + 1] * (i + 1);
    }
}

double evaluate_polynomial(double* coeffs, int degree, double a) {
    double result = 0, pow_a = 1;
    for (int i = 0; i <= degree; i++) {
        result += coeffs[i] * pow_a;
        pow_a *= a;
    }
    return result;
}

enum Errors polynomial_rearrangement(double a, double** result_coeffs, int degree, ...) {
    va_list args;
    va_start(args, degree);

    double* coeffs = (double*)malloc((degree + 1) * sizeof(double));
    if (!coeffs) {
        va_end(args);
        return INVALID_MEMORY;
    }

    for (int i = 0; i <= degree; i++) {
        coeffs[i] = va_arg(args, double);
    }
    va_end(args);

    *result_coeffs = (double*)malloc((degree + 1) * sizeof(double));
    if (!*result_coeffs) {
        free(coeffs);
        return INVALID_MEMORY;
    }   

    double* derivative_coeffs = (double*)malloc(degree * sizeof(double));
    if (!derivative_coeffs) {
        free(coeffs);
        free(*result_coeffs);
        return INVALID_MEMORY;  
    }
    double* tmp_coeffs = (double*)malloc((degree + 1) * sizeof(double));
    if (!tmp_coeffs) {
        free(coeffs);
        free(derivative_coeffs);
        free(*result_coeffs);
        return INVALID_MEMORY;  
    }
    for (int i = 0; i <= degree; i++) {
        tmp_coeffs[i] = coeffs[i];
    }

    double* factorials = (double*)malloc((degree + 1) * sizeof(double));
    if (!factorials) {
        free(coeffs);
        free(derivative_coeffs);
        free(tmp_coeffs);
        free(*result_coeffs);
        return INVALID_MEMORY;
    }
    factorials[0] = 1;
    for (int i = 1; i <= degree; i++) {
        factorials[i] = factorials[i - 1] * i;
    }

    for (int i = 0; i <= degree; i++) {
        (*result_coeffs)[i] = evaluate_polynomial(tmp_coeffs, degree - i, a) / factorials[i];
        if (i < degree) {
            polynomial_derivative(tmp_coeffs, degree - i, derivative_coeffs);
            for (int j = 0; j < degree - i; j++) {
                tmp_coeffs[j] = derivative_coeffs[j];
            }
            tmp_coeffs[degree - i] = 0;
        }
    }

    free(coeffs);
    free(derivative_coeffs);
    free(tmp_coeffs);
    free(factorials);
    return OK;
}

double evaluate_rearranged_polynomial(double* coeffs, int degree, double a, double x) {
    double result = 0;
    double x_minus_a = x - a, pow_m = 1;
    for (int i = 0; i <= degree; i++) {
        result += coeffs[i] * pow_m;
        pow_m *= x_minus_a;
    }
    return result;
}