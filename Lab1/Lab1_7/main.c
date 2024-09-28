#include <stdio.h>
#include "main.h"

int main(int argc, char **argv) { 
    if (argc == 5 || argc == 4){
        if (is_valid_flag(argv[1]) != OK){
            printf("INVALID_INPUT\n");
            return INVALID_INPUT;
        }

        enum Errors err = OK;

        switch (argv[1][1])
        {
        case 'r':
            if (argc != 5){
                err = INVALID_INPUT;
                break;
            }

            err = merge_files(argv[2], argv[3], argv[4]);
            if (err != OK)
                break;
            else
                printf("Everything is done\n");
            break;
        case 'a':
            if (argc != 4){
                err = INVALID_INPUT;
                break;
            }
            
            err = process_file(argv[2], argv[3]);
            if (err != OK)
                break;
            else
                printf("Everything is done\n");
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
        case ERROR_OPEN_FILE:
            printf("ERROR_OPEN_FILE in %c", argv[1][1]);
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
