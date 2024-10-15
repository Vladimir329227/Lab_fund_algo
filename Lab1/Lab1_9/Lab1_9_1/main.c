#include <stdio.h>
#include "main.h"

int main(int argc, char **argv) { 
    if (argc != 3){
        printf("INVALID_INPUT");
        return INVALID_INPUT;
    }

    long int start, stop;
    if(convert_str_to_int(argv[1], &start, 10) != OK ||
        convert_str_to_int(argv[2], &stop, 10) != OK ||
        start > stop){
        printf("INVALID_INPUT");
        return INVALID_INPUT;
    }

    long int* result_array = NULL;
    if(fill_array(&result_array, ARRAY_SIZE, start, stop) != OK)
    {
        printf("INVALID_MEMORY");
        return INVALID_MEMORY;
    }

    printf("source array: \n");
    for(int i = 0; i < ARRAY_SIZE; ++i)
        printf("%li ", result_array[i]);
    printf("\n");

    if (swap_min_max(&result_array, ARRAY_SIZE) != OK){
        free(result_array);
        printf("INVALID_INPUT");
        return INVALID_INPUT;
    }

    printf("the resulting array: \n");
    for(int i = 0; i < ARRAY_SIZE; ++i)
        printf("%li ", result_array[i]);
    printf("\n");

    free(result_array);
    return OK;
}
