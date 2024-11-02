#ifndef MAIN_H_FLAG
#define MAIN_H_FLAG
#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#define LEN_NAME 70

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    ERROR_OPEN_FILE,
};

struct Employee{
    unsigned int id;
    char name[LEN_NAME], surname[LEN_NAME];
    float salary;
};

enum Errors read_file(struct Employee** result, FILE* file, size_t* size);

int compare(const void * x1, const void * x2);

int reverse_compare(const void * x1, const void * x2);

enum Errors is_valid_flag(const char *str);

enum Errors wreite_file(struct Employee* result, FILE* file, size_t size);

enum Errors is_file_path(const char *path1, const char *path2);

#endif