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
#include <stdarg.h>
#include <string.h>

#define HASH_SPREAD (long long int)pow(10, 8)
#define BASE 256

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    ERROR_OPEN_FILE,
};

enum Errors find_word(int** result, int* cur_elem, const char* str, const int count, ...);

#endif