#ifndef MAIN_H_FLAG
#define MAIN_H_FLAG

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
};

enum Errors convert_str_to_int (const char *str, long long int * result, int base);

#endif