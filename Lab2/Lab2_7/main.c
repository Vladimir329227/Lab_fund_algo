#include <stdio.h>
#include "main.h"

double example_function(double x) {
    return x * x - 2;
}

int main() { 
    double a = 0.0, b = 2.0, epsilon = 0.0001, result;

    if (dichotomy_method(example_function, a, b, epsilon, &result) != OK)
        printf("Error!\n");
    else
        printf("Result: %lf\n", result);

    return OK;
}