#include <stdio.h>
#include "main.h"

int main() { 
    int* result;    
    if (check_finite_representation(&result, 5, 3, 0.5, 0.25, 0.2) != OK)
        return INVALID_INPUT;
    for (int i = 0; i < 3; i++)
        printf("%i ", result[i]);
    printf("\n");
    free(result);

    return OK;
}