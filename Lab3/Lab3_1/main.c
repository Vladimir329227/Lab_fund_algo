#include "main.h"

int main() { 
    char* result = NULL;
    for (int i = -32; i <= 32; i++)
    {
        convert_to_base(32, i, &result);
        printf("%s\n", result);
        free(result);
    }

    return OK;
}