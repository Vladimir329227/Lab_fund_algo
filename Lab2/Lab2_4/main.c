#include <stdio.h>
#include "main.h"

int main(int argc, char **argv) { 
    enum Errors err;
    if (argc < 2)
        return INVALID_INPUT;

    if (is_valid_flag(argv[1]) != OK){
        printf("INVALID_INPUT");
        return INVALID_INPUT;
    }

    switch (argv[1][1])
    {
    case '1':
        int result_1;

        err = is_convex_polygon(&result_1, 4, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0);
        if (err != OK)
            break;

        if (result_1 == 0)
            printf("Collinear");
        else if (result_1 == 1)
            printf("Clockwise");
        else if (result_1 == 2)
            printf("Counterclockwise");
        break;
    case '2':
        double result_2;

        err = evaluate_polynomial(&result_2, 3.0, 3, 1.0, -2.0, 3.0, 4.0);
        if (err != OK)
            break;

        printf("Result 2: %f\n", result_2);
        break;
    case '3':
        int result_3;

        err = find_kaprekar_numbers(&result_3, 10, 3, "45", "1", "11");
        if (err != OK)
            break;

        printf("Result 3: %i\n", result_3);
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