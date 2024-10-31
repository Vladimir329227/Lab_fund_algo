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

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    ERROR_OPEN_FILE,
};

struct Employee{
    unsigned int id;
    char name[70], surname[70];
    float salary;
};

enum Errors read_file(struct Employee** result, FILE* file, size_t* size);

int compare(const void * x1, const void * x2);

int reverse_compare(const void * x1, const void * x2);

enum Errors is_valid_flag(const char *str);

enum Errors wreite_file(struct Employee* result, FILE* file, size_t size);

#endif