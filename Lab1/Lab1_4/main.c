#include <stdio.h>
#include "main.h"

int main(int argc, char **argv) { 
    if (argc >= 2){
        enum Errors err = OK;
        if (is_valid_flag(argv[1]) == OK){
            char* response_file_name;
            if (argv[1][1] == 'n')
            {
                if (argc >= 4)
                {
                    response_file_name = argv[3];
                }
                else{
                    printf("INVALID_INPUT");
                    return INVALID_INPUT;
                }
            }
            else{
                if (argc >= 3)
                {
                    response_file_name = (char*)malloc((strlen(argv[2])+5)*sizeof(char));
                    if (response_file_name == NULL){
                        printf("INVALID_MEMORY in %c", argv[1][1]);
                        return INVALID_MEMORY;
                    }
                    snprintf(response_file_name, strlen(argv[2])+5, "out_%s", argv[2]);
                }
                else{
                    printf("INVALID_INPUT");
                    return INVALID_INPUT;
                }
            }


            if (is_valid_filename(response_file_name) != OK || is_valid_filename(argv[2]) != OK)
            {
                printf("INVALID_INPUT incorrect file name");
                return INVALID_INPUT;
            }
            

            switch ((argv[1][1] == 'n')?argv[1][2]:argv[1][1])
            {
            case 'd':
                err = remove_numbers_from_file(argv[2], response_file_name);
                if (err != OK)
                    break;
                else
                    printf("Everything is done\n");
                break;
            case 'i':
                err = count_number_of_letters(argv[2], response_file_name);
                if (err != OK)
                    break;
                else
                    printf("Everything is done\n");
                break;
            case 's':
                err = count_number_of_different_characters(argv[2], response_file_name);
                if (err != OK)
                    break;
                else
                    printf("Everything is done\n");
                break;
            case 'a':
                err = replacing_characters_to_ASCII_code(argv[2], response_file_name);
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
                printf("INVALID_INPUT in %c", (argv[1][1] == 'n')?argv[1][2]:argv[1][1]);
                return INVALID_INPUT;
            case INVALID_MEMORY:
                printf("INVALID_MEMORY in %c", (argv[1][1] == 'n')?argv[1][2]:argv[1][1]);
                return INVALID_MEMORY;
            default:
                break;
            } 
        }
        else{
            printf("INVALID_INPUT");
            return INVALID_INPUT;
        }
    }
    else {
        printf("INVALID_INPUT");
        return INVALID_INPUT;
    }
    
    return OK;
}
