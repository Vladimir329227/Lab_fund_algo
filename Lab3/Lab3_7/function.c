#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

int isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12 || year < 1) 
        return 0;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        daysInMonth[1] = 29;
    if (day < 1 || day > daysInMonth[month - 1])
        return 0;
    return 1;
}

int is_valid_data(const char *name, const char *surname, const char *patronymic, const char sex, const float salary){
    if (name == NULL || surname == NULL || patronymic == NULL || salary < 0.0)
        return 0;
    if (sex != 'M' && sex != 'W')
        return 0;
    for (size_t i = 0; i < strlen(name); i++)
        if (!isalpha(name[i]))
            return 0;
    for (size_t i = 0; i < strlen(surname); i++)
        if (!isalpha(surname[i]))
            return 0;
    for (size_t i = 0; i < strlen(patronymic); i++)
        if (!isalpha(patronymic[i]))
            return 0;
    if (salary > roundf(salary * 100) / 100)
        return 0;
    return 1;
}

int compare_dates(const struct Liver* liver1, const struct Liver* liver2) {
    if (liver1->year != liver2->year) {
        return liver1->year - liver2->year;
    }
    if (liver1->month != liver2->month) {
        return liver1->month - liver2->month;
    }
    return liver1->day - liver2->day;
}

void free_list(struct StringlyLinkedList* head) {
    struct StringlyLinkedList* current = head;
    while (current != NULL) {
        struct StringlyLinkedList* next = current->next;
        free(current);
        current = next;
    }
}

enum Errors add_sorted(struct StringlyLinkedList** head, struct Liver new_data) {
    if (!head)
        return INVALID_INPUT;
    struct StringlyLinkedList* new_node = (struct StringlyLinkedList*)malloc(sizeof(struct StringlyLinkedList));
    if (new_node == NULL)
        return INVALID_MEMORY;
    new_node->data = new_data;
    new_node->next = NULL;

    if (*head == NULL || compare_dates(&new_data, &(*head)->data) < 0) {
        new_node->next = *head;
        *head = new_node;
        return OK;
    }

    struct StringlyLinkedList* current = *head;
    while (current->next != NULL && compare_dates(&new_data, &current->next->data) >= 0) {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
    return OK;
}

enum Errors read_file(struct StringlyLinkedList** result, FILE* file, size_t* size){
    if (!file || !size)
        return INVALID_INPUT;
    *size = 0;
    char name[LEN_NAME], surname[LEN_NAME], patronymic[LEN_NAME];
    int year = 0, month = 0, day = 0;
    float salary = 0.0;
    char sex;
    int t = fscanf(file, "%s %s %s", name, surname, patronymic);
    while (t == 3) {
        if (sscanf(patronymic, "%d.%d.%d", &year, &month, &day) != 3){
            t = fscanf(file, "%d.%d.%d",  &year, &month, &day);
            if (t != 3)
                return INVALID_INPUT;
        }
        else{
            patronymic[0] = '\0';
        }
        t = fscanf(file, " %c %f\n", &sex, &salary);
        if (t != 2)
            return INVALID_INPUT;
        if (!is_valid_data(name, surname, patronymic, sex, salary) || !isValidDate(day, month, year))
            return INVALID_INPUT;

        (*size)++;
        struct Liver data;
        strcpy(data.name, name);
        strcpy(data.surname, surname);
        strcpy(data.patronymic, patronymic);
        data.year = year;
        data.month = month;
        data.day = day;
        data.sex = sex;
        data.salary = salary;
        add_sorted(result, data);
        if (!(*result)){
            (*size)--;
            return INVALID_MEMORY;
        }
        t = fscanf(file, "%s %s %s", name, surname, patronymic);
    }

    return OK;
}

enum Errors wreite_file(struct StringlyLinkedList* result, FILE* file, size_t size){
    if (!file || !result)
        return INVALID_INPUT;
    struct StringlyLinkedList* current = result;
    for (size_t i = 0; i < size; i++){
        if (current->data.patronymic[0] == '\0')
            fprintf(file, "%s %s %d.%d.%d %c %.2f\n", current->data.name, current->data.surname, current->data.year, current->data.month, current->data.day, current->data.sex, current->data.salary);
        else
            fprintf(file, "%s %s %s %d.%d.%d %c %.2f\n", current->data.name, current->data.surname, current->data.patronymic, current->data.year, current->data.month, current->data.day, current->data.sex, current->data.salary);
        current = current->next;
    }
    return OK;
}

enum Errors add_modification(struct Modification** history, size_t* history_size, struct Liver old_data, struct Liver data, enum Operation operation) {
    if (!history || !history_size)
        return INVALID_INPUT;
    *history = (struct Modification*)realloc(*history, (*history_size + 1) * sizeof(struct Modification));
    if (!(*history))
        return INVALID_MEMORY;
    (*history)[*history_size].data = data;
    (*history)[*history_size].old_data = old_data;
    (*history)[*history_size].operation = operation;
    (*history_size)++;
    return OK;
}

enum Errors search_liver(struct StringlyLinkedList* head, int param, const char* value) {
    struct StringlyLinkedList* current = head;
    while (current != NULL) {
        if (param == 1 && strcmp(current->data.name, value) == 0) {
            printf("%s %s %s %d.%d.%d %c %.2f\n", current->data.name, current->data.surname, current->data.patronymic, current->data.year, current->data.month, current->data.day, current->data.sex, current->data.salary);
        } else if (param == 2 && strcmp(current->data.surname, value) == 0) {
            printf("%s %s %s %d.%d.%d %c %.2f\n", current->data.name, current->data.surname, current->data.patronymic, current->data.year, current->data.month, current->data.day, current->data.sex, current->data.salary);
        } else if (param == 3 && strcmp(current->data.patronymic, value) == 0) {
            printf("%s %s %s %d.%d.%d %c %.2f\n", current->data.name, current->data.surname, current->data.patronymic, current->data.year, current->data.month, current->data.day, current->data.sex, current->data.salary);
        } else if (param == 4 && current->data.year == atoi(value)) {
            printf("%s %s %s %d.%d.%d %c %.2f\n", current->data.name, current->data.surname, current->data.patronymic, current->data.year, current->data.month, current->data.day, current->data.sex, current->data.salary);
        } else if (param == 5 && current->data.month == atoi(value)) {
            printf("%s %s %s %d.%d.%d %c %.2f\n", current->data.name, current->data.surname, current->data.patronymic, current->data.year, current->data.month, current->data.day, current->data.sex, current->data.salary);
        } else if (param == 6 && current->data.day == atoi(value)) {
            printf("%s %s %s %d.%d.%d %c %.2f\n", current->data.name, current->data.surname, current->data.patronymic, current->data.year, current->data.month, current->data.day, current->data.sex, current->data.salary);
        } else if (param == 7 && current->data.sex == value[0]) {
            printf("%s %s %s %d.%d.%d %c %.2f\n", current->data.name, current->data.surname, current->data.patronymic, current->data.year, current->data.month, current->data.day, current->data.sex, current->data.salary);
        } else if (param == 8 && current->data.salary == atof(value)) {
            printf("%s %s %s %d.%d.%d %c %.2f\n", current->data.name, current->data.surname, current->data.patronymic, current->data.year, current->data.month, current->data.day, current->data.sex, current->data.salary);
        }
        current = current->next;
    }
    return OK;
}

enum Errors remove_liver(struct StringlyLinkedList** head, struct Liver data) {
    if (!head)
        return INVALID_INPUT;
    struct StringlyLinkedList* current = *head;
    struct StringlyLinkedList* prev = NULL;
    while (current != NULL && (strcmp(current->data.name, data.name) != 0 || strcmp(current->data.surname, data.surname) != 0 || current->data.year != data.year || current->data.month != data.month || current->data.day != data.day)) {
        prev = current;
        current = current->next;
    }
    if (current != NULL) {
        if (prev != NULL) {
            prev->next = current->next;
        } else {
            *head = current->next;
        }
        free(current);
        return OK;
    }
    return INVALID_INPUT;
}

enum Errors update_liver(struct StringlyLinkedList** head, struct Liver old_data, struct Liver new_data) {
    enum Errors err = OK;
    err = remove_liver(head, old_data);
    if (err != OK)
        return err;
    err = add_sorted(head, new_data);
    if (err != OK)
        return err;
    return OK;
}

enum Errors update_liver_mod(struct StringlyLinkedList** head, struct Liver old_data, struct Liver new_data, struct Modification** history, size_t* history_size) {
    if (!head || !history || !history_size)
        return INVALID_INPUT;
    if (!head)
        return INVALID_INPUT;
    struct StringlyLinkedList* current = *head;
    while (current != NULL && (strcmp(current->data.name, old_data.name) != 0 || strcmp(current->data.surname, old_data.surname) != 0 || current->data.year != old_data.year || current->data.month != old_data.month || current->data.day != old_data.day)) {
        current = current->next;
    }
    if (current == NULL)
        return INVALID_INPUT;
    old_data = current->data;
    enum Errors err = update_liver(head, old_data, new_data);
    if (err == OK) {
        if (add_modification(history, history_size, old_data, new_data, UPDATE) != OK)
            return INVALID_MEMORY;
    }
    return err;
}

enum Errors remove_liver_mod(struct StringlyLinkedList** head, struct Liver data, struct Modification** history, size_t* history_size, size_t* size) {
    enum Errors err = remove_liver(head, data);
    if (err == OK) {
        if (add_modification(history, history_size, data, data, REMOVE) != OK)
            return INVALID_MEMORY;
        (*size)--;
    }
    return err;
}


enum Errors add_liver_mod(struct StringlyLinkedList** head, struct Liver data, struct Modification** history, size_t* history_size, size_t* size) {
    if (!is_valid_data(data.name, data.surname, data.patronymic, data.sex, data.salary) || !isValidDate(data.day, data.month, data.year) || !size || !head || !history || !history_size)
            return INVALID_INPUT;
    enum Errors err = add_sorted(head, data);
    if (err == OK) {
        if (add_modification(history, history_size, data, data, ADD) != OK)
            return INVALID_MEMORY;
        (*size)++;
    }
    return err;
}

void print_list(struct StringlyLinkedList* head) {
    struct StringlyLinkedList* current = head;
    while (current != NULL) {
        printf("%s %s %s %d.%d.%d %c %.2f\n", current->data.name, current->data.surname, current->data.patronymic, current->data.year, current->data.month, current->data.day, current->data.sex, current->data.salary);
        current = current->next;
    }
    printf("----------------------------------------------------------------\n");
}

enum Errors undo_modifications(struct StringlyLinkedList** head, struct Modification** history, size_t* history_size, size_t* size) {
    size_t undo_count = (*history_size) / 2;
    enum Errors err = OK;
    for (size_t i = 0; i < undo_count; i++) {
        struct Modification modification = (*history)[*history_size - 1];
        printf("Kod operacji: %d\n", modification.operation);
        printf("modification data: %s %s %s %d.%d.%d %c %.2f\n", modification.data.name, modification.data.surname, modification.data.patronymic, modification.data.year, modification.data.month, modification.data.day, modification.data.sex, modification.data.salary);
        (*history_size)--;
        if (modification.operation == ADD) {
            //err = remove_liver(head, modification.data);
            struct StringlyLinkedList* current = *head;
            struct StringlyLinkedList* prev = NULL;
            while (current != NULL && compare_dates(&current->data, &modification.data) != 0) {
                prev = current;
                current = current->next;
            }
            if (current != NULL) {
                if (prev != NULL) {
                    prev->next = current->next;
                } else {
                    *head = current->next;
                }
                free(current);
                (*size)--;
            }
        } else if (modification.operation == REMOVE) {
            err = add_sorted(head, modification.data);
            if (err == INVALID_MEMORY)
                return err;
            (*size)++;
        } else if (modification.operation == UPDATE) {
            err = remove_liver(head, modification.data);
            if (err == INVALID_MEMORY)
                return err;
            err = add_sorted(head, modification.old_data);
            if (err == INVALID_MEMORY)
                return err;
        }
    }
    return OK;
}