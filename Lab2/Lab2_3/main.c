#include <stdio.h>
#include "main.h"

int main() { 
    int* res, cur_elem;
    enum Errors err = find_word(&res, &cur_elem, "test\ntest", 4, "test1.txt", "test1.txt", "test2.txt", "test3.txt");
    if (err != OK){
        if (err == INVALID_INPUT)
            printf("INVALID_INPUT");
        else if (err == INVALID_MEMORY)
            printf("INVALID_MEMORY");
        else if (err == ERROR_OPEN_FILE)
            printf("ERROR_OPEN_FILE");
        return err;
    }

    for (int i = 0; i < cur_elem; i++)
    {
        printf("line %i; simbol %i\n", res[i], res[i+1]);
        i++;
    }
    
    printf("Result: %i\n", cur_elem / 2);
    free(res);

    return OK;
}