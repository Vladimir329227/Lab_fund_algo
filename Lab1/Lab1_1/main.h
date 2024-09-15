#ifndef MAIN_H_FLAG
#define MAIN_H_FLAG

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
};

enum Errors find_flag_in_input(const char **argv, int *rez);

#endif