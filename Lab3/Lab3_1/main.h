#ifndef MAIN_H_FLAG
#define MAIN_H_FLAG

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#define SIZE_INT 32

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    ERROR_OPEN_FILE,
};

enum Errors convert_to_base(const int base, int num, char **result);

#endif