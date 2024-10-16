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

enum Errors geometric_mean(double* result, int count, ...) {
    if (count <= 0 || !result)
        return INVALID_INPUT; 

    va_list args = NULL;
    va_start(args, count);

    double product = 1.0;
    for (int i = 0; i < count; ++i) {
        double value = va_arg(args, double);
        if (value <= 0.0) {
            va_end(args);
            return INVALID_INPUT;
        }

        if (!isnormal(product) || isinf(product)) {
            va_end(args);
            return INVALID_INPUT; 
        }

        product *= value;
    }

    va_end(args);

    *result = pow(product, 1.0 / count);
    return OK;
}

enum Errors fast_power(double base, int exponent, double* result) {
    if (base == 0.0){
        *result = 0.0;
        return OK;
    }

    if(exponent < 0)
        return fast_power(1.0 / base,  -1 * exponent, result);

    if (exponent == 0) {
        *result = 1.0;
        return OK;
    }

    double half_power;
    if (fast_power(base, exponent / 2, &half_power) != OK)
        return INVALID_INPUT;

    double cur_result = half_power * half_power;
    if (!isnormal(cur_result) || isinf(cur_result)) 
        return INVALID_INPUT;

    if (exponent % 2 != 0) {
        cur_result *= base;
        if (!isnormal(cur_result) || isinf(cur_result)) {
            return INVALID_INPUT;
        }
    }

    *result = cur_result;
    return OK;
}