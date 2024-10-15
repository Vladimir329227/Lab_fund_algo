#include <stdio.h>
#include "main.h"

int main(int argc, char **argv) { 
    if (argc == 3){
        enum Errors err = OK;

        err = process_files(argv[1], argv[2]);

        switch (err)
        {
        case INVALID_INPUT:
            printf("INVALID_INPUT");
            return INVALID_INPUT;
        case INVALID_MEMORY:
            printf("INVALID_MEMORY");
            return INVALID_MEMORY;
        case ERROR_OPEN_FILE:
            printf("ERROR_OPEN_FILE");
            return ERROR_OPEN_FILE;
        case OK:
            printf("Everything is done\n");
            return ERROR_OPEN_FILE;
        default:
            break; 
        }         
    }
    else {
        printf("INVALID_INPUT");
        return INVALID_INPUT;
    }
    
    return OK;
}
