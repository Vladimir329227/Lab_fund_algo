#include "main.h"

enum Errors is_valid_flag(const char *str)
{
    if (str == NULL)
        return INVALID_INPUT;
    if ((str[0] == '-' || str[0] == '/') && str[2] == '\0')
        return OK;
    return INVALID_INPUT;
}

enum Errors convert_str_to_int(const char *str, long long int * result, int base)
{
    char *endptr;
    *result = strtoll(str, &endptr, base);

    if (*result == LLONG_MAX || *result == LLONG_MIN)
        return INVALID_INPUT;
    else if (*endptr != '\0') 
        return INVALID_INPUT;

    return OK;
}

/*
0 - Коллинеарные
1, 2 - По часовой стрелке или против часовой стрелки
*/
int orientation(double p1x, double p1y, double p2x, double p2y, double p3x, double p3y) 
{
    double val = (p2y - p1y) * (p3x - p2x) - (p2x - p1x) * (p3y - p2y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

enum Errors is_convex_polygon(int* result, const int count, ...) 
{
    if (count < 3 || !result) 
        return INVALID_INPUT;

    va_list args;
    va_start(args, count);

    double* x = (double*)malloc(count * sizeof(double));
    double* y = (double*)malloc(count * sizeof(double));

    if (!x || !y) {
        va_end(args);
        free(x);
        free(y);
        return INVALID_MEMORY;
    }

    for (int i = 0; i < count; ++i) {
        x[i] = va_arg(args, double);
        y[i] = va_arg(args, double);
    }

    va_end(args);

    int is_convex = 1;
    int prev_orientation = 0;

    for (int i = 0; i < count; ++i) {
        int j = (i + 1) % count;
        int k = (i + 2) % count;
        int current_orientation = orientation(x[i], y[i], x[j], y[j], x[k], y[k]);

        if (current_orientation == 0) {
            is_convex = 0;
            break;
        }

        if (prev_orientation != 0 && current_orientation != prev_orientation) {
            is_convex = 0;
            break;
        }

        prev_orientation = current_orientation;
    }

    *result = is_convex;

    free(x);
    free(y);

    return OK;
}


enum Errors evaluate_polynomial(double *result, double x, int count, ...) {
    if (count < 1 || !result) 
        return INVALID_INPUT;

    va_list args;
    va_start(args, count);

    *result = 0.0;
    double current_power = 1.0;
    double coefficient;
    for (int i = 0; i <= count; ++i) {
        coefficient = va_arg(args, double);
        *result += coefficient * current_power;
        if (isinf(*result) || isnan(*result)) {
            va_end(args);
            return INVALID_INPUT;
        }
        current_power *= x;
    }

    va_end(args);
    return OK;
}

int is_kaprekar(long long int num) {
    if (num == 0 || num == 1)
        return 1; 

    long long int square = (long long int)num * num;
    int num_digits = 0;
    long long int temp = square;

    while (temp > 0) {
        num_digits++;
        temp /= 10;
    }

    long long int left, right;
    for (int i = 1; i < num_digits; i++) {
        left = square / (long long int)pow(10, i);
        right = square % (long long int)pow(10, i);
        if (left + right == num)
            return 1;
    }

    return 0;
}

enum Errors find_kaprekar_numbers(int* result, int base, int count, ...) {
    if (!result || base < 0)
        return INVALID_INPUT;
    
    va_list args;
    va_start(args, count);

    *result = 0;

    long long int num;

    for (int i = 0; i < count; ++i) {
        if (convert_str_to_int(va_arg(args, char*), &num, base) != OK)
            return INVALID_INPUT;
        if (is_kaprekar(num))
            (*result)++;
    }

    va_end(args);
    return OK;
}