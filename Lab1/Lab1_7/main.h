#ifndef MAIN_H_FLAG
#define MAIN_H_FLAG

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    ERROR_OPEN_FILE,
};

void convert_to_base4(char *dest, char c, int size);

enum Errors is_valid_flag(const char *str);

enum Errors convert_str_to_double(const char *str, double * result);

enum Errors merge_files(const char* file1, const char* file2, const char* output_file);

enum Errors process_file(const char *input_path, const char *output_path);

#endif