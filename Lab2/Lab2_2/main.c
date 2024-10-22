#include <stdio.h>
#include "main.h"

int main(int argc, char **argv) { 
    enum Errors err = OK;

    if (argc < 2)
        return INVALID_INPUT;

    if (is_valid_flag(argv[1]) != OK){
        printf("INVALID_INPUT");
        return INVALID_INPUT;
    }

    switch (argv[1][1])
    {
    case '1':
        double res_1;
        err = geometric_mean(&res_1, 5, 1.9, 1.0, 5.9, 2.9, 1.3);
        if (err != OK)
            break;
        printf("Result 1: %f\n", res_1);
        break;
    case '2':
        double res_2;
        err = fast_power(5.2, 2, &res_2);
        if (err != OK)
            break;
        printf("Result 2: %f\n", res_2);
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
    
    
    return OK;
}