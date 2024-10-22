#include <stdio.h>
#include "main.h"

int main(int argc, char **argv) { 
    if (argc >= 2){
        enum Errors err = OK;
        if (is_valid_flag(argv[1]) == OK){
            switch (argv[1][1])
            {
            case 'q':
                if (argc == 6){
                    double eps;
                    switch (convert_str_to_double(argv[2], &eps))
                    {
                    case INVALID_INPUT:
                        printf("INVALID_INPUT in namber");
                        return INVALID_INPUT;
                    case INVALID_MEMORY:
                        printf("INVALID_MEMORY in namber");
                        return INVALID_MEMORY;
                    default:
                        break;
                    } 
                    double parameter_array_q[3];
                    int number_results_q;
                    QuadraticSolution* result_q;
                    for (int i = 0; i < 3; i++)
                    {
                        switch (convert_str_to_double(argv[3+i], &(parameter_array_q[i])))
                        {
                        case INVALID_INPUT:
                            printf("INVALID_INPUT in namber");
                            return INVALID_INPUT;
                        case INVALID_MEMORY:
                            printf("INVALID_MEMORY in namber");
                            return INVALID_MEMORY;
                        default:
                            break;
                        } 
                    }

                    err = enumeration_quadratic_equation_parameters(eps, parameter_array_q, &result_q, &number_results_q);
                    if (err != OK)
                        break;
                    for (int i = 0; i < number_results_q; i++){
                        print_quadratic_solution(result_q[i]);                    
                    }
                }
                else
                    err = INVALID_INPUT;
                break;
            case 'm':
                if (argc == 4){
                    long long int parameter_a, parameter_b;
                    int result_m;
                    switch (convert_str_to_int(argv[2], &parameter_a, 10))
                    {
                    case INVALID_INPUT:
                        printf("INVALID_INPUT in namber");
                        return INVALID_INPUT;
                    case INVALID_MEMORY:
                        printf("INVALID_MEMORY in namber");
                        return INVALID_MEMORY;
                    default:
                        break;
                    } 
                    switch (convert_str_to_int(argv[3], &parameter_b, 10))
                    {
                    case INVALID_INPUT:
                        printf("INVALID_INPUT in namber");
                        return INVALID_INPUT;
                    case INVALID_MEMORY:
                        printf("INVALID_MEMORY in namber");
                        return INVALID_MEMORY;
                    default:
                        break;
                    } 
                    err = is_number_multiple(parameter_a, parameter_b, &result_m);
                    if (err != OK)
                        break;
                    if (result_m == 1)
                        printf("Multiple number");
                    else
                        printf("Number is not a multiple");
                }
                else
                    err = INVALID_INPUT;
                break;
            case 't':
                if (argc == 6){
                    double eps;
                    int result_t;
                    switch (convert_str_to_double(argv[2], &eps))
                    {
                    case INVALID_INPUT:
                        printf("INVALID_INPUT in namber");
                        return INVALID_INPUT;
                    case INVALID_MEMORY:
                        printf("INVALID_MEMORY in namber");
                        return INVALID_MEMORY;
                    default:
                        break;
                    } 
                    double parameter_array_q[3];
                    for (int i = 0; i < 3; i++)
                    {
                        switch (convert_str_to_double(argv[3+i], &(parameter_array_q[i])))
                        {
                        case INVALID_INPUT:
                            printf("INVALID_INPUT in namber");
                            return INVALID_INPUT;
                        case INVALID_MEMORY:
                            printf("INVALID_MEMORY in namber");
                            return INVALID_MEMORY;
                        default:
                            break;
                        } 
                    }
                    
                    err = is_sides_triangle_possible(eps, parameter_array_q, &result_t);
                    if (err != OK)
                        break;
                    if (result_t == 1)
                        printf("The sides can be the lengths of the sides of a right triangle");
                    else
                        printf("The sides cannot be the lengths of the sides of a right triangle");
                }
                else
                    err = INVALID_INPUT;
                break;
            default:
                printf("Flag not found\n");
                break;
            }

            switch (err)
            {
            case INVALID_INPUT:
                printf("INVALID_INPUT in %c", argv[1][1]);
                return INVALID_INPUT;
            case INVALID_MEMORY:
                printf("INVALID_MEMORY in %c", argv[1][1]);
                return INVALID_MEMORY;
            default:
                break;
            } 
        }
        else{
            printf("INVALID_INPUT");
            return INVALID_INPUT;
        }
    }
    else {
        printf("INVALID_INPUT");
        return INVALID_INPUT;
    }
    
    return OK;
}
