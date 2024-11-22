#include "main.h"

int compare_memory_cells(const void *a, const void *b) {
    return strcmp(((MemoryCell *)a)->name, ((MemoryCell *)b)->name);
}

MemoryCell* binary_search(MemoryArray *array, const char *name) {
    MemoryCell key = {.name = (char *)name};
    MemoryCell *result = bsearch(&key, array->cells, array->size, sizeof(MemoryCell), compare_memory_cells);
    return result;
}

enum Errors add_variable(MemoryArray *array, const char *name, int value) {
    if (!name || !array) 
        return INVALID_INPUT;
    if (array->size == array->capacity) {
        array->capacity = array->capacity == 0 ? 1 : array->capacity * 2;
        MemoryCell *t;
        t = (MemoryCell *)realloc(array->cells, array->capacity * sizeof(MemoryCell));
        if (!t)
            return INVALID_MEMORY;
        array->cells = t;
    }
    array->cells[array->size].name = strdup(name);
    array->cells[array->size].value = value;
    array->size++;
    qsort(array->cells, array->size, sizeof(MemoryCell), compare_memory_cells);
    return OK;
}

enum Errors free_memory_array(MemoryArray *array) {
    if (!array) 
        return INVALID_INPUT;
    for (size_t i = 0; i < array->size; i++) {
        free(array->cells[i].name);
    }
    free(array->cells);
    array->cells = NULL;
    array->size = 0;
    array->capacity = 0;
    return OK;
}

enum Errors evaluate_expression(MemoryArray *array, const char *expr, int* result) {
    char op = '\0', var_name[MAX_LINE_LENGTH];
    int var_index = 0, num = 0;
    *result = 0;

    while (*expr) {
        if (isalpha(*expr)) {
            var_index = 0;
            while (isalpha(*expr))
                var_name[var_index++] = *expr++;
            var_name[var_index] = '\0';
            MemoryCell *cell = binary_search(array, var_name);
            if (!cell)
                return INVALID_INPUT;
            if (op == '\0') {
                *result = cell->value;
            } else {
                switch (op) {
                    case '+': *result += cell->value; break;
                    case '-': *result -= cell->value; break;
                    case '*': *result *= cell->value; break;
                    case '/': *result /= cell->value; break;
                    case '%': *result %= cell->value; break;
                }
            }
        } else if (isdigit(*expr)) {
            num = 0;
            while (isdigit(*expr))
                num = num * 10 + (*expr++ - '0');
            if (op == '\0') {
                *result = num;
            } else {
                switch (op) {
                    case '+': *result += num; break;
                    case '-': *result -= num; break;
                    case '*': *result *= num; break;
                    case '/': *result /= num; break;
                    case '%': *result %= num; break;
                }
            }
        } else if (*expr == '+' || *expr == '-' || *expr == '*' || *expr == '/' || *expr == '%') {
            op = *expr++;
        } else {
            expr++;
        }
    }
    return OK;
}

enum Errors execute_instructions(MemoryArray *array, const char *filename) {
    if (!filename || !array) 
        return INVALID_INPUT;
    FILE *file = fopen(filename, "r");
    if (!file) 
        return ERROR_OPEN_FILE;

    char line[MAX_LINE_LENGTH];
    char var_name[MAX_LINE_LENGTH], expr[MAX_LINE_LENGTH];
    int var_index = 0, expr_index = 0;
    int i = 0, value = 0;
    while (fgets(line, sizeof(line), file)) {
        var_index = 0;
        expr_index = 0;
        i = 0;

        while (line[i] && isalpha(line[i])) 
            var_name[var_index++] = line[i++];
        var_name[var_index] = '\0';

        if (line[i] == '=') {
            i++;
            while (line[i] && line[i] != ';')
                expr[expr_index++] = line[i++];

            expr[expr_index] = '\0';
            if (evaluate_expression(array, expr, &value) != OK){
                printf("Error: Invalid expression: %s\n", expr);
                return INVALID_INPUT;
            }
            MemoryCell *cell = binary_search(array, var_name);
            if (cell)
                cell->value = value;
            else
                if (add_variable(array, var_name, value) != OK) 
                    return INVALID_MEMORY;
        } else if (strncmp(var_name, "print", 5) == 0) {
            if (line[i] == ';') {
                for (size_t j = 0; j < array->size; j++) {
                    printf("%s = %d\n", array->cells[j].name, array->cells[j].value);
                }
            } else {
                while (line[i] && line[i] != ';')
                    var_name[var_index++] = line[i++];

                var_name[var_index] = '\0';
                char* var_name_copy = var_name;
                var_name_copy += 6;
                MemoryCell *cell = binary_search(array, var_name_copy);
                if (cell) {
                    printf("%s = %d\n", cell->name, cell->value);
                } else {
                    printf("Error: Invalid variable name: %s\n", var_name);
                    return INVALID_INPUT;
                }
            }
        }
    }

    fclose(file);
    return OK;
}