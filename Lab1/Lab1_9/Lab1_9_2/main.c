#include <stdio.h>
#include "main.h"

#define ARRAY_SIZE_A 10
#define ARRAY_SIZE_B 10


int main() { 
    short start = -1000, stop = 1000;
    srand(time(NULL));
    
    short* result_a = NULL, *result_b = NULL;
    if(fill_array(&result_a, ARRAY_SIZE_A, start, stop) != OK || fill_array(&result_b, ARRAY_SIZE_B, start, stop) != OK)
    {
        if (!result_a)
            free(result_a);
        printf("INVALID_MEMORY");
        return INVALID_MEMORY;
    }

    printf("source array A: \n");
    for(int i = 0; i < ARRAY_SIZE_A; ++i)
        printf("%hi ", result_a[i]);
    printf("\n");

    short* result_c = NULL;

    if(generate_array_with_find_closest(result_a, ARRAY_SIZE_A, result_b, ARRAY_SIZE_B, &result_c) != OK)
    {
        free(result_a);
        free(result_b);
        printf("INVALID_INPUT");
        return INVALID_INPUT;
    }

    printf("source array C: \n");
    for(int i = 0; i < ARRAY_SIZE_A; ++i)
        printf("%hi ", result_c[i]);
    printf("\n");
    
    printf("source array B: \n");
    for(int i = 0; i < ARRAY_SIZE_B; ++i)
        printf("%hi ", result_b[i]);
    printf("\n");

    free(result_a);
    free(result_b);
    free(result_c);
    return OK;
}
