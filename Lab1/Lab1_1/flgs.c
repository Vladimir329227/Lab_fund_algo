#include "main.h"
#include <cstddef>

enum Errors find_flag_in_input(const char **argv, int *rez){
    if (rez == NULL){
        rez = (int)malloc(sizeof(int));
        if (rez == NULL) return INVALID_MEMORY;
    }
    int is_find_flag = 0, is_find_namber = 0;
    for(int i=1;i<3;i++){
        if (argv[i][0] == '-' || argv[i][0] == '/' && argv[i][2] == '\0'){
            is_find_flag = 1;
            *rez = i;
        }
        if (argv[i][0] - '0' >= 0 && argv[i][0] - '0' <= 9){
            is_find_namber = 1;
            for(int o=0;o<strlen(argv[i]);o++)
                if (!(argv[i][0] - '0' >= 0 && argv[i][0] - '0' <= 9))
                    is_find_namber = 0;
        }
    }
    if (is_find_namber == 0 || is_find_flag == 0)
        return INVALID_INPUT;
    return OK;
}