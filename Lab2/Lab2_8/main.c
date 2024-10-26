#include <stdio.h>
#include "main.h"

int main() { 
    int base = 10;
    char* num1 = "0000101000";
    char* num2 = "";
    char* num3 = "00000310";

    char* result;
    enum Errors err = sumInBase(&result, base, 3, num1, num2, num3);
    if (err != OK) 
        printf("Error: %d\n", err);
    else{
        printf("%s\n", result);
    }
    free(result);

    return OK;
}