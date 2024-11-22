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

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    ERROR_OPEN_FILE,
};

typedef struct {
    char *name;
    int value;
} MemoryCell;

typedef struct {
    MemoryCell *cells;
    size_t size;
    size_t capacity;
} MemoryArray;

enum Errors execute_instructions(MemoryArray *array, const char *filename);

enum Errors free_memory_array(MemoryArray *array);


#endif