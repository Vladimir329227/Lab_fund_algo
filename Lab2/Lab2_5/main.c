#include <stdio.h>
#include "main.h"

#define NUM 13

int main() { 
    char buffer[1000];
    FILE *file = fopen("test.txt", "w");
    if (!file) 
        return ERROR_OPEN_FILE;
    //overfprintf(file, "%d\n%Ro\n%f\n%mi\n", 47, 47, 47.0, 47);
    //oversprintf(buffer, "%d\n%Ro\n%f\n%mi\n", 47, 47, (float)47.0, 47);
    overfprintf(file, "%%\n%i\n%i\n%Ro\n1", 0, 2, 3, 4);

    oversprintf(buffer, "%%\n%i\n%i\n%Ro\n1", 0, 2, 3, 4);

    //oversprintf(buffer, "123456790asdf\n%d\n%Ro\n%f\n%mi\n%Zr\n", NUM, NUM, NUM, NUM, NUM);
    printf("%s\n", buffer);

     printf("%%");
    return OK;
}