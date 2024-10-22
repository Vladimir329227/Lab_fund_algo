#include <stdio.h>
#include "main.h"

int main(int argc, char **argv) { 
    enum Errors err = OK;

    if (argc < 3)
        return INVALID_INPUT;

    if (is_valid_flag(argv[1]) != OK){
        printf("INVALID_INPUT");
        return INVALID_INPUT;
    }

    switch (argv[1][1])
    {
    case 'l':
        if (argc != 3){
            err = INVALID_INPUT;
            break;
        }
        int size;
        err = my_strlen(argv[2], &size);
        if (err != OK){
            break;
        }
        printf("String length: %i\n", size);
        break;
    case 'r':
        if (argc != 3){
            err = INVALID_INPUT;
            break;
        }
        char* rez_r = NULL;
        err = my_reversed(argv[2], &rez_r);

        if (err != OK){
            free(rez_r);
            break;
        }
        
        printf("String reversed: %s\n", rez_r);
        free(rez_r);
        break;
    case 'u':
        if (argc != 3){
            err = INVALID_INPUT;
            break;
        }
        char* rez_u = NULL;
        err = my_capitalize(argv[2], &rez_u);

        if (err != OK){
            free(rez_u);
            break;
        }
        
        printf("String capitalize: %s\n", rez_u);
        free(rez_u);
        break;
    case 'n':
        if (argc != 3){
            err = INVALID_INPUT;
            break;
        }
        char* rez_n = NULL;
        err = my_nedo_sort(argv[2], &rez_n);

        if (err != OK){
            free(rez_n);
            break;
        }
        
        printf("String sort: %s\n", rez_n);
        free(rez_n);
        break;
    case 'c':
        if (argc <= 3){
            err = INVALID_INPUT;
            break;
        }

        int count_str = argc - 3;
        long long int seed;
        if(convert_str_to_int(argv[2], &seed, 10) != OK)
        {
            printf("INVALID_INPUT");
            return INVALID_INPUT;
        }

        char* rez_c = NULL;
        err = my_concotenation((argv + 3), &rez_c, count_str, seed);

        if (err != OK){
            free(rez_c);
            break;
        }
        
        printf("String concotenation: %s\n", rez_c);
        free(rez_c);
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