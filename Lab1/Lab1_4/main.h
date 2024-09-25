#ifndef MAIN_H_FLAG
#define MAIN_H_FLAG

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
};

enum Errors is_valid_flag(const char *str);

enum Errors is_valid_filename(const char *file_name);

enum Errors remove_numbers_from_file(const char* input_file, const char* response_file);

enum Errors count_number_of_letters(const char* input_file_name, const char* response_file_name);

enum Errors count_number_of_different_characters(const char* input_file_name, const char* response_file_name);

enum Errors replacing_characters_to_ASCII_code(const char* input_file_name, const char* response_file_name);

#endif