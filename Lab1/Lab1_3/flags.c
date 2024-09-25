#include "main.h"

enum Errors is_valid_flag(const char *str)
{
    if (str == NULL)
        return INVALID_INPUT;
    if ((str[0] == '-' || str[0] == '/') && str[2] == '\0')
        return OK;
    return INVALID_INPUT;
}

enum Errors convert_str_to_double(const char *str, double * result)
{
    if (str == NULL || result == NULL)
        return INVALID_INPUT;
    char *endptr;
    *result = strtod(str, &endptr);
    if (*result == HUGE_VAL || *result == -HUGE_VAL){
        return INVALID_INPUT;
    } else if (*endptr != '\0') {
        return INVALID_INPUT;
    }
    return OK;
}

enum Errors convert_str_to_int(const char *str, long long int * result, const int base)
{
    if (str == NULL || result == NULL)
        return INVALID_INPUT;
    char *endptr;
    *result = strtoll(str, &endptr, base);

    if (*result == LLONG_MAX || *result == LLONG_MIN)
        return INVALID_INPUT;
    else if (*endptr != '\0') 
        return INVALID_INPUT;

    return OK;
}

enum Errors convert_kvadr_uravn(const double eps, const double a, const double b, const double c, QuadraticSolution* result)
{
    if (result == NULL)
        return INVALID_INPUT;
    double discriminant = 0;
    result->col_vo_solutions = 0;
    result->solution1.real = 0;
    result->solution1.imag = 0;
    result->solution2.real = 0;
    result->solution2.imag = 0;
    result->a = a;
    result->b = b;
    result->c = c;    
    if (fabs(a) < eps) {
        if (fabs(b) < eps) {
            if (fabs(c) < eps) {
                result->col_vo_solutions = -1;
            } else {
                result->col_vo_solutions = 0;
            }
        } else {
            result->col_vo_solutions = 1;
            result->solution1.real = -c / b;
            if (result->solution1.real < eps) {
                result->solution1.real = fabs(result->solution1.real);
            }
        }
    } else {
        discriminant = b * b - 4 * a * c;
        if (discriminant >= eps) {
            result->col_vo_solutions = (discriminant > eps) ? 2 : 1;
            result->solution1.real = (-b + sqrt(discriminant)) / (2 * a);
            if (result->solution1.real < eps) {
                result->solution1.real = fabs(result->solution1.real);
            }
            result->solution2.real = (-b - sqrt(discriminant)) / (2 * a);
            if (result->solution2.real < eps) {
                result->solution2.real = fabs(result->solution1.real);
            }
            if (fabs(result->solution1.real - result->solution2.real) < eps){
                result->col_vo_solutions = 1;
            }
        } else {
            result->col_vo_solutions = 2;
            result->solution1.real = -b / (2 * a);
            if (result->solution1.real < eps) {
                result->solution1.real = fabs(result->solution1.real);
            }
            result->solution1.imag = sqrt(-discriminant) / (2 * a);
            if (result->solution1.imag < eps) {
                result->solution1.imag = fabs(result->solution1.real);
            }
            result->solution2.real = -b / (2 * a);
            if (result->solution2.real < eps) {
                result->solution2.real = fabs(result->solution1.real);
            }
            result->solution2.imag = -sqrt(-discriminant) / (2 * a);
            if (result->solution2.imag < eps) {
                result->solution2.imag = fabs(result->solution1.real);
            }
            if (fabs(result->solution1.real - result->solution2.real) < eps && fabs(result->solution1.imag - result->solution2.imag) < eps){
                result->col_vo_solutions = 1;
            }
        }
    }
    return OK;
}

void print_quadratic_solution(const QuadraticSolution result){
    printf("a=%f; b=%f; c=%f\n" ,result.a, result.b, result.c);
    if (result.col_vo_solutions == -1) {
        printf("Infinite number of solutions\n");
    } else if (result.col_vo_solutions == 0) {
        printf("No solutions\n");
    } else if (result.col_vo_solutions == 1) {
        printf("x = %lf\n", result.solution1.real);
    } else {
        if (result.solution1.imag == 0 && result.solution2.imag == 0) {
            printf("x1 = %lf, x2 = %lf\n", result.solution1.real, result.solution2.real);
        } else {
            printf("x1 = %lf + %lfi, x2 = %lf + %lfi\n",
                   result.solution1.real, result.solution1.imag,
                   result.solution2.real, result.solution2.imag);
        }
    }
}

enum Errors enumeration_quadratic_equation_parameters(const double eps, const double* array_numbers, QuadraticSolution** result, int* number_results){
    if (array_numbers == NULL || number_results == NULL || result == NULL) 
        return INVALID_INPUT;
    int parameter_array[9][3];
    *number_results = 0;
    int p, is_unical;
    for (int i = 0; i < 3; i++)
    {
        for (int o = 0; o < 3; o++)
        {
            if (o != i)
            {
                p = 3 - i - o;
                is_unical = 1;
                for (int q = 0; q < *number_results; q++)
                    if (parameter_array[q][0] == array_numbers[i] && parameter_array[q][1] == array_numbers[o] && parameter_array[q][2] == array_numbers[p])
                        is_unical = 0;
                if (is_unical == 1){
                    parameter_array[*number_results][0] = array_numbers[i];
                    parameter_array[*number_results][1] = array_numbers[o];
                    parameter_array[*number_results][2] = array_numbers[p];
                    (*number_results)++;
                }
            }
        }
    }

    *result = (QuadraticSolution*)malloc(*number_results*sizeof(QuadraticSolution));
    if (result == NULL)
    {
        free(*result);
        return INVALID_MEMORY;
    }

    for (int i = 0; i < *number_results; i++){
        convert_kvadr_uravn(eps, parameter_array[i][0], parameter_array[i][1], parameter_array[i][2], &((*result)[i]));
    }    
    return OK;
}

/*
1 - кратно
0 - не кратно
*/
enum Errors is_number_multiple(const long long int a, const long long int b, int* result){
    if (result == NULL)
        return INVALID_INPUT;
    if (a % b == 0)
        *result=1;
    else
        *result=0;
    return OK;
}

/*
1 - стороны могут являться длинами сторон прямоугольного треугольника
0 - стороны не могут являться длинами сторон прямоугольного треугольника
*/
enum Errors is_sides_triangle_possible(const double eps, const double sides[3], int* result){
    if (result == NULL)
        return INVALID_INPUT;
    double sorted_sides[3];
    for (int i = 0; i < 3; i++)
        sorted_sides[i] = sides[i];
    double temp;
    for (int i = 0; i < 2; i++) {
        for (int j = i + 1; j < 3; j++) {
            if (sorted_sides[i] > sorted_sides[j]) {
                temp = sorted_sides[i];
                sorted_sides[i] = sorted_sides[j];
                sorted_sides[j] = temp;
            }
        }
    }

    if (fabs(sorted_sides[0] * sorted_sides[0] + sorted_sides[1] * sorted_sides[1] - sorted_sides[2] * sorted_sides[2]) < eps) {
        *result = 1;
    } else {
        *result = 0;
    }
    return OK;
}

