#include "main.h"

enum Errors remove_comments(char *line) {
    if (!line) 
        return INVALID_INPUT;
    char *comment_start = strchr(line, '%');
    if (comment_start) *comment_start = '\0';

    char *multiline_start = strchr(line, '{');
    if (multiline_start) {
        char *multiline_end = strchr(line, '}');
        if (multiline_end) *multiline_end = '\0';
        *multiline_start = '\0';
    }
    return OK;
}


enum Errors get_variable_value(char var_name, bool_vector vars[MAX_VARS], bool_vector* result) {
    if (var_name >= 'A' && var_name <= 'Z') {
        *result = vars[var_name - 'A'];
        return OK;
    } else {
        return INVALID_INPUT;        
    }
}

enum Errors eval_expression(char *expr, bool_vector vars[MAX_VARS], bool_vector* result) {
    char var1, var2, op[2];
    op[1] = '\0';
    if (sscanf(expr, "%c %s %c", &var1, op, &var2) == 3) {
        bool_vector val1, val2;
        if (get_variable_value(var1, vars, &val1) != OK || get_variable_value(var2, vars, &val2) != OK)
            return INVALID_INPUT;

        switch (op[0]) {
            case '&': 
                *result = val1 & val2;
                break;
            case '-':
                if (op[1] == '>') *result = ~val1 | val2;
                else if (op[1] == '<') *result = val1 | ~val2;
                break;
            case '~': 
                *result = ~(val1 ^ val2);
                break;
            case '<':
                if (op[1] == '>') *result = val1 ^ val2;
                break;
            case '+':
                if (op[1] == '>') *result = ~val1 & val2;
                break;
            case '?': 
                *result = ~(val1 & val2);
                break;
            case '!': 
                *result = ~val1 | ~val2;
                break;
            default:
                return INVALID_INPUT;
        }
        return OK;
    } else if (sscanf(expr, "\\%c", &var1) == 1) {
        bool_vector val;
        if (get_variable_value(var1, vars, &val) != OK)
            return INVALID_INPUT;
        *result = ~val;
        return OK;
    } else {
        return INVALID_INPUT;
    }
    return INVALID_INPUT;
}

enum Errors itoa_base(unsigned long long value, char *result, int base) {
    if (base < 2 || base > 36 || !result) 
        return INVALID_INPUT;

    char buffer[MAX_LINE_LENGTH];
    char *ptr = buffer;
    char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int iteration = 0;
    do {
        *ptr++ = digits[value % base];
        value /= base;
        iteration++;
    } while (value && iteration < MAX_LINE_LENGTH);

    if (iteration == MAX_LINE_LENGTH)
        return INVALID_INPUT;

    *ptr = '\0';

    char *start = buffer;
    char *end = ptr - 1;
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }

    strcpy(result, buffer);
    return OK;
}

enum Errors execute_instruction(char *instruction, bool_vector vars[MAX_VARS], FILE *trace_file) {
    if (!instruction) 
        return INVALID_INPUT;
    char var_name;
    char expr[MAX_LINE_LENGTH];
    int base, is_valid = 1;
    bool_vector value;
    if (sscanf(instruction, "%c := %[^;];", &var_name, expr) == 2) {
        if (var_name >= 'A' && var_name <= 'Z') {
            if (isdigit(expr[0])) {
                value = strtoull(expr, NULL, 10);
            } else {
                if (eval_expression(expr, vars, &value) != OK) {
                    return INVALID_INPUT;
                }
            }
            vars[var_name - 'A'] = value;
            if (trace_file) {
                fprintf(trace_file, "Executed: %s\n", instruction);
                fprintf(trace_file, "Result: %llu\n", value);
            }
        } else {
            if (trace_file) {
                fprintf(trace_file, "Error: Invalid variable name in instruction: %s\n", instruction);
            }
        }
    } else if (sscanf(instruction, "read(%c, %d);", &var_name, &base) == 2) {
        if (var_name >= 'A' && var_name <= 'Z' && (base >= 2 && base <= 36)) {
            char input[MAX_LINE_LENGTH];
            printf("Enter value for %c in base %d: ", var_name, base);
            scanf("%s", input);
            for (size_t i = 0; i < strlen(input); i++) {
                if (input[i] >= '0' && input[i] <= '9' && input[i] - '0' >= base){
                    is_valid = 0;
                    break;
                }
                else if (input[i] >= 'A' && input[i] <= 'Z' && input[i] - 'A' >= base){
                    is_valid = 0;
                    break;
                }
                else if (input[i] >= 'a' && input[i] <= 'z' && input[i] - 'a' >= base){
                    is_valid = 0;
                    break;
                }
                else if (!((input[i] >= '0' && input[i] <= '9') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z'))){
                    is_valid = 0;
                    break;
                }
            }
            if (is_valid) {
                value = strtoull(input, NULL, base);
                if (value != ULLONG_MAX && input[0] != '\0') {
                    vars[var_name - 'A'] = value;
                    if (trace_file) {
                        fprintf(trace_file, "Read: %s\n", instruction);
                        fprintf(trace_file, "Value: %llu\n", value);
                    }
                }
                else
                {
                    if (trace_file) {
                        fprintf(trace_file, "Error: Invalid input in instruction: %s\n", instruction);
                    }
                }
            }
            else
            {
                if (trace_file) {
                    fprintf(trace_file, "Error: Invalid input in instruction: %s\n", instruction);
                }
            }
        } else {
            if (trace_file) {
                fprintf(trace_file, "Error: Invalid variable name in instruction: %s\n", instruction);
            }
        }
    } else if (sscanf(instruction, "write(%c, %d);", &var_name, &base) == 2) {
        if (var_name >= 'A' && var_name <= 'Z') {
            value = vars[var_name - 'A'];
            char result[MAX_LINE_LENGTH];
            if (itoa_base(value, result, base) == OK){
                printf("Value of %c in base %d: %s\n", var_name, base, result);
                if (trace_file) {
                    fprintf(trace_file, "Write: %s\n", instruction);
                    fprintf(trace_file, "Value: %llu\n", value);
                }
            } else {
                if (trace_file) {
                    fprintf(trace_file, "Error: Invalid variable name in instruction: %s\n", instruction);
                }
            }
        } else {
            if (trace_file) {
                fprintf(trace_file, "Error: Invalid variable name in instruction: %s\n", instruction);
            }
        }
    } else {
        if (trace_file) {
            fprintf(trace_file, "Error: Invalid instruction: %s\n", instruction);
        }
    }
    return OK;
}