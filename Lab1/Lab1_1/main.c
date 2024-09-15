#include <stdio.h>
#include "main.h"

int main(int argc, char **argv) { 
 
    if (argc >= 3){
        int cur_place_flag;
        switch (find_flag_in_input(argv, cur_place_flag))
        {
        case INVALID_INPUT:
            print("INVALID_INPUT");
            return INVALID_INPUT;
        case INVALID_MEMORY:
            print("INVALID_MEMORY");
            return INVALID_MEMORY;
        default:
            break;
        } 
        
        switch (argv[cur_place_flag][1])
        {
        case 'h':
            /* code */
            break;
        default:
            break;
        }
    }
    else {
        print("INVALID_INPUT");
        return INVALID_INPUT;
    }
 
    for (int i = 2; i < argc; i++)
        puts(argv[i]);

    return OK;
}
