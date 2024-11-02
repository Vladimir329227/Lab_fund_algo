#ifndef MAIN_H_FLAG
#define MAIN_H_FLAG
#define _GNU_SOURCE

#include <errno.h>
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

struct Liver{
    char name[LEN_NAME], surname[LEN_NAME], patronymic[LEN_NAME];
    short year, month, day;
    char sex;
    float salary;
};

struct StringlyLinkedList{
    struct StringlyLinkedList* next;
    struct Liver data;
};

struct Modification {
    struct Liver data, old_data;
    enum Operation { ADD, REMOVE, UPDATE } operation;
};

enum Errors is_valid_flag(const char *str);

enum Errors is_file_path(const char *path1, const char *path2);

enum Errors read_file(struct StringlyLinkedList** result, FILE* file, size_t* size);

enum Errors wreite_file(struct StringlyLinkedList* result, FILE* file, size_t size);

void free_list(struct StringlyLinkedList* head);

enum Errors add_modification(struct Modification** history, size_t* history_size, struct Liver old_data, struct Liver data, enum Operation operation);

enum Errors undo_modifications(struct StringlyLinkedList** head, struct Modification** history, size_t* history_size, size_t* size);

enum Errors search_liver(struct StringlyLinkedList* head, int param, const char* value);

enum Errors add_liver_mod(struct StringlyLinkedList** head, struct Liver data, struct Modification** history, size_t* history_size, size_t* size);

enum Errors remove_liver_mod(struct StringlyLinkedList** head, struct Liver data, struct Modification** history, size_t* history_size, size_t* size);

enum Errors update_liver_mod(struct StringlyLinkedList** head, struct Liver old_data, struct Liver new_data, struct Modification** history, size_t* history_size);

void print_list(struct StringlyLinkedList* head);

#endif