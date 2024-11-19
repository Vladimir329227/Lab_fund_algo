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

struct BusStop{
    char name[LEN_NAME];
    struct BusStop *next;
    time_t time_arrival, time_departure;
    int flag;
};

struct Bus{
    unsigned int number;
    struct BusStop *start;
};

enum Errors ParseStopFile(const char *filename, struct Bus **result, int *count);

void freeBus(struct Bus *bus, int number);

void printBus(struct Bus *bus, int number);

enum Errors UserMain(struct Bus *buses, int count);

#endif