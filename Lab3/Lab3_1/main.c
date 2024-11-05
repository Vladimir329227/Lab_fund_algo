#include "main.h"

int main() { 
    char* result = NULL;
    convert_to_base(32, 5000, &result);
    printf("%s\n", result);
    free(result);
    return OK;
}