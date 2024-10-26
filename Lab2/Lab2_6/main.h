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

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    ERROR_OPEN_FILE,
};

int overfscanf(FILE *stream, const char *format, ...);

int oversscanf(const char *format, ...);

#endif