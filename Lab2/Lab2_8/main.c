#include <stdio.h>
#include "main.h"

int main() { 
    int base = 16;
    char* num1 = "0000000000000000000000000000001";
    char* num2 = "ffff";
    char* num3 = "ff";
    char* num4 = "1";

    char* result;
    enum Errors err = sumInBase(&result, base, 4, num1, num2, num3, num4);
    if (err != OK) 
        printf("Error: %d\n", err);
    else{
        printf("%s\n", result);
    }
    //free(result);

    return OK;
}