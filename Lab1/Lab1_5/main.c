#include <stdio.h>
#include "main.h"

int main(int argc, char **argv) { 
    if (argc >= 3){
        double eps, x;
        switch (convert_str_to_double(argv[1], &eps))
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
        switch (convert_str_to_double(argv[2], &x))
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
        double result[4];
        enum Errors err[4];
        int n = 0;
        err[n] = example_a(x, eps, &(result[n]));
        n++;
        err[n] = example_b(x, eps, &(result[n]));
        n++;
        err[n] = example_с(x, eps, &(result[n]));
        n++;
        err[n] = example_d(x, eps, &(result[n]));
        n++;
        char* str = "abcd";
        for (int i = 0; i < n; i++)
        {
            switch (err[i])
            {
            case INVALID_INPUT:
                printf("%c)INVALID_INPUT\n", str[i]);
                break;
            case INVALID_MEMORY:
                printf("%c)INVALID_MEMORY\n", str[i]);
                break;
            case OK:
                printf("%c)%f\n", str[i], result[i]);
                break;
            default:
                break;
            } 
        }
        
    }
    else {
        printf("INVALID_INPUT");
        return INVALID_INPUT;
    }
    
    return OK;
}
