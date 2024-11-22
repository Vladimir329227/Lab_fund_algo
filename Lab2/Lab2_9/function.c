#include "main.h"

enum Errors has_finite_representation(double number, int base, int* result) {
    if (number <= 0 || number >= 1 || !result || base < 2 || base > 36) 
        return INVALID_INPUT; 

    double fraction = number;
    long int denominator = 1, iterations = 0;

    while (fraction - (unsigned int)fraction <= EPSILON  && iterations < MAX_ITERATIONS) {
        if (fraction > DBL_MAX / base || fraction < DBL_MIN / base || denominator > LONG_MAX / base) {
            result = 0;
            printf("Overflow\n");
            return OK;
        }
        fraction *= base;
        denominator *= base;
        iterations++;
    }

    int temp = denominator;
    while (temp % base == 0) {
        temp /= base;
    }

    *result = (temp == 1);
    return OK;
}

enum Errors check_finite_representation(int** result, int base, int count, ...) {
    if (base < 2 || base > 36 || count == 0 || !result)
        return INVALID_INPUT;
    
    *result = (int*)malloc(sizeof(int) * count);
    if (!*result)
        return INVALID_MEMORY;

    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        double number = va_arg(args, double);
        if (has_finite_representation(number, base, &((*result)[i])) != OK){
            free(*result);
            return INVALID_INPUT;
        }
    }

    va_end(args);
    return OK;
}