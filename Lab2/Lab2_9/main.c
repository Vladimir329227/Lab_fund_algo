#include <stdio.h>
#include "main.h"

int main() { 
    int* result;    
    if (check_finite_representation(&result, 5, 3, 0.16234, 0.2, 0.1) != OK)
        return INVALID_INPUT;
    for (int i = 0; i < 3; i++)
        printf("%i ", result[i]);
    printf("\n");
    free(result);

    return OK;
}