#include <stdio.h>
#include "main.h"

#define NUM 13

int main() { 
    FILE *file = fopen("test.txt", "r");
    if (!file) 
        return ERROR_OPEN_FILE;
    
    int romanValue;
    unsigned int zeckendorfValue;
    int customValue;

    overfscanf(file, "%Ro %Zr %CV", &romanValue, &zeckendorfValue, 16, &customValue);
    printf("Roman: %d, Zeckendorf: %u, Custom: %d\n", romanValue, zeckendorfValue, customValue);

    fclose(file);

    //const char *str = "XIX    \t \n\n10101 1A 18 2.01 10101 1A";
    int romanValue2;
    float f;
    unsigned int zeckendorfValue2, zeckendorfValue3;
    int customValue2;
    int i;
    int customValue3;

    oversscanf("%Ro test%Zrtest test%99[^!] %CV %i%f%% %Zr %CV ", &romanValue2, &zeckendorfValue2, 16, &customValue2, &i, &f, &zeckendorfValue3, 16, &customValue3);
    //oversscanf("11 1A","%i %CV", &i, 16, &customValue3);
    //printf("%i %d \n", i, customValue3);

    printf("Roman: %d, Zeckendorf: %u, Custom: %d \n%i %f Zeckendorf: %u, Custom: %d\n", romanValue2, zeckendorfValue2, customValue2, i, f, zeckendorfValue3, customValue3);

    
    int integer;
    char character;
    char string[100];

    if (scanf("%dtest%c %99[^\n]", &integer, &character, string) == 3) {
        printf(": %d\n", integer);
        printf(": %c\n", character);
        printf(": %s\n", string);
    } else {
        printf(".\n");
    }

    return OK;
}