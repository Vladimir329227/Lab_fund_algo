#include <stdio.h>
#include "main.h"

#define ARRAY_SIZE 10

int main() { 
    long int start = -1000, stop = 1000;
    srand(time(NULL));
    
    long int* result_a = NULL, *result_b = NULL;
    if(fill_array(&result_a, ARRAY_SIZE, start, stop) != OK || fill_array(&result_b, ARRAY_SIZE, start, stop))
    {
        printf("INVALID_MEMORY");
        return INVALID_MEMORY;
    }

    printf("source array A: \n");
    for(int i = 0; i < ARRAY_SIZE; ++i)
        printf("%li ", result_a[i]);
    printf("\n");

    printf("source array B: \n");
    for(int i = 0; i < ARRAY_SIZE; ++i)
        printf("%li ", result_b[i]);
    printf("\n");

    long int* result_c = NULL;

    if(generate_array_with_find_closest(result_a, ARRAY_SIZE, result_b, ARRAY_SIZE, &result_c) != OK)
    {
        printf("INVALID_INPUT");
        return INVALID_INPUT;
    }

    printf("source array C: \n");
    for(int i = 0; i < ARRAY_SIZE; ++i)
        printf("%li ", result_c[i]);
    printf("\n");
    

    return OK;
}
