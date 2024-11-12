#include <stdio.h>
#include "main.h"

int main() { 
    double a = 2.0;
    int degree = 2;
    double* result_coeffs;

    polynomial_rearrangement(a, &result_coeffs, degree, 1.0, -2.0, 1.0);
    /*
    double a = 0.0;
    int degree = 4;
    double* result_coeffs;
    
    polynomial_rearrangement(a, &result_coeffs, degree, -2.0, 1.0, -3.0, 0.0, 1.0);
*/
    for (int i = 0; i <= degree; i++) {
        printf("g%d = %f\n", i, result_coeffs[i]);
    }

    double test_points[] = {0, 1, 2, 3, 4};
    int num_points = sizeof(test_points) / sizeof(test_points[0]);

    double x, f_value;
    double g_value[] = {1.0, 4.0, 9.0, 16.0, 25.0};
    //double g_value[] = {55.0, 210.0, 553.0, 1192.0, 2259.0};
    for (int i = 0; i < num_points; i++) {
        x = test_points[i];
        f_value = evaluate_polynomial(result_coeffs, degree, x);
        printf("x = %f: f(x) = %f, g(x) = %f\n", x, f_value, g_value[i]);
    }

    free(result_coeffs);

    return OK;
}