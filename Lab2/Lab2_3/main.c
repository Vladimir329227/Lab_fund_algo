#include <stdio.h>
#include "main.h"

int main() { 
    int res;
    enum Errors err = find_word(&res, "test", 4, "test1.txt", "test1.txt", "test2.txt", "test3.txt");
    if (err != OK){
        if (err == INVALID_INPUT)
            printf("INVALID_INPUT");
        else if (err == INVALID_MEMORY)
            printf("INVALID_MEMORY");
        else if (err == ERROR_OPEN_FILE)
            printf("ERROR_OPEN_FILE");
        return err;
    }
    printf("Result: %i\n", res);
    
    return OK;
}