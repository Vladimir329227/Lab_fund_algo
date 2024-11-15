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

    #define HASH_SIZE 128
    #define LINE_SIZE 256

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    ERROR_OPEN_FILE,
};

typedef struct Node {
    char *def_name;
    char *value;
    struct Node *next;
} Node;

typedef struct {
    Node *table[HASH_SIZE];
    int size;
    int count;
} HashTable;

enum Errors process_file(const char *filename);

#endif