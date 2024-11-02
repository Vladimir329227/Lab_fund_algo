#include "main.h"

enum Errors is_valid_flag(const char *str)
{
    if (str == NULL)
        return INVALID_INPUT;
    if ((str[0] == '-' || str[0] == '/') && str[2] == '\0')
        return OK;
    return INVALID_INPUT;
}

enum Errors is_file_path(const char *path1, const char *path2)
{
    if (!path1 || !path2)
        return INVALID_INPUT;
    
    char real_path1[PATH_MAX];
    char real_path2[PATH_MAX];

    if (realpath(path1,real_path1) == NULL || realpath(path2,real_path2) == NULL) 
        return ERROR_OPEN_FILE;
    
    if (strcmp(real_path1, real_path2) == 0)
        return INVALID_INPUT;
    return OK;
}

int is_valid_data(const char *name, const char *surname, float salary){
    if (name == NULL || surname == NULL || salary < 0.0)
        return 0;
    for (size_t i = 0; i < strlen(name); i++)
        if (!isalpha(name[i]))
            return 0;
    for (size_t i = 0; i < strlen(surname); i++)
        if (!isalpha(surname[i]))
            return 0;
    if (salary > roundf(salary * 100) / 100)
        return 0;
    return 1;
}

enum Errors read_file(struct Employee** result, FILE* file, size_t* size){
    if (!file || !result || !size)
        return INVALID_INPUT;
    *size = 0;
    char name[LEN_NAME], surname[LEN_NAME];
    unsigned int id = 0;
    float salary = 0.0;
    int t = fscanf(file, "%u %s %s %f\n", &id, name, surname, &salary);
    while (t == 4) {
        if (!is_valid_data(name, surname, salary))
            return INVALID_INPUT;
        (*size)++;
        if ((*size) == 1)
            *result = (struct Employee*)malloc(sizeof(struct Employee));
        else
            *result = (struct Employee*)realloc(*result, sizeof(struct Employee)*(*size));
        if (!(*result)){
            (*size)--;
            return INVALID_MEMORY;
        }
        (*result)[(*size) - 1].id = id;
        strcpy((*result)[(*size) - 1].name, name);
        strcpy((*result)[(*size) - 1].surname, surname);
        (*result)[(*size) - 1].salary = salary;
        t = fscanf(file, "%u %s %s %f\n", &id, name, surname, &salary);
    }

    return OK;
}

int reverse_compare(const void * x1, const void * x2)
{
    if (((struct Employee*)x1)->salary > ((struct Employee*)x2)->salary)
        return 1;
    else if (((struct Employee*)x1)->salary < ((struct Employee*)x2)->salary)
        return -1;
    else if (strcmp(((struct Employee*)x1)->surname, ((struct Employee*)x2)->surname))
        return strcmp(((struct Employee*)x1)->name, ((struct Employee*)x2)->name);
    else if (strcmp(((struct Employee*)x1)->name, ((struct Employee*)x2)->name))
        return strcmp(((struct Employee*)x1)->surname, ((struct Employee*)x2)->surname);
    else if (((struct Employee*)x1)->id > ((struct Employee*)x2)->id)
        return 1;
    else if (((struct Employee*)x1)->id < ((struct Employee*)x2)->id)
        return -1;
    return 0;
}

int compare(const void * x1, const void * x2){
    return reverse_compare(x2, x1);
}

enum Errors wreite_file(struct Employee* result, FILE* file, size_t size){
    if (!file || !result)
        return INVALID_INPUT;
    for (size_t i = 0; i < size; i++)
        fprintf(file, "%u %s %s %.2f\n", result[i].id, result[i].name, result[i].surname, result[i].salary);
    return OK;
}