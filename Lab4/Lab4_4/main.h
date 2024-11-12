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

#define MAX_VARS 26
#define MAX_LINE_LENGTH 256

typedef unsigned long long bool_vector;

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    ERROR_OPEN_FILE,
};

enum Errors remove_comments(char *line);

enum Errors execute_instruction(char *instruction, bool_vector vars[MAX_VARS], FILE *trace_file);

#endif