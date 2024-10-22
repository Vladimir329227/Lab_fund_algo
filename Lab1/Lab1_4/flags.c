#include "main.h"

enum Errors is_valid_flag(const char *str)
{
    if (str == NULL)
        return INVALID_INPUT;
    if ((str[0] == '-' || str[0] == '/') && (str[2] == '\0' || (str[3] == '\0' && str[1] == 'n')))
        return OK;
    return INVALID_INPUT;
}

enum Errors is_valid_filename(const char *file_name) {
    if (file_name == NULL || *file_name == '\0') {
        return INVALID_INPUT;
    }

    const char *invalid_chars = ":*?\"<>|";
    for (const char *p = file_name; *p != '\0'; ++p) {
        if (strchr(invalid_chars, *p) != NULL) {
            return INVALID_INPUT;
        }
    }

    return OK;
}
enum Errors remove_numbers_from_file(const char* input_file_name, const char* response_file_name)
{
    if (input_file_name == NULL || response_file_name == NULL)
        return INVALID_INPUT;
    FILE *input_file = fopen(input_file_name, "r");
    if (input_file == NULL)
        return INVALID_INPUT;

    FILE *response_file = fopen(response_file_name, "w");
    if (response_file == NULL){
        fclose(input_file);
        return INVALID_INPUT;
    }

    int c;
    while ((c = fgetc(input_file)) != EOF) {
        if (c < '0' || c > '9') {
            fputc(c, response_file);
        }
    }

    fclose(input_file);
    fclose(response_file);
    return OK;
}

int count_latin_letters(const char *str) {
    if (str == NULL)
        return INVALID_INPUT;
    int count = 0;
    while (*str) {
        if ((*str >= 'A' && *str <= 'Z') || (*str >= 'a' && *str <= 'z')) {
            count++;
        }
        str++;
    }
    return count;
}

enum Errors count_number_of_letters(const char* input_file_name, const char* response_file_name){
    if (input_file_name == NULL || response_file_name == NULL)
        return INVALID_INPUT;
    FILE *input_file = fopen(input_file_name, "r");
    if (input_file == NULL)
        return INVALID_INPUT;

    FILE *response_file = fopen(response_file_name, "w");
    if (response_file == NULL){
        fclose(input_file);
        return INVALID_INPUT;
    }

    int line_count = 0;
    int in_line = 0; 
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), input_file) != NULL) {
        size_t len = strlen(buffer);
        if (in_line) {
            line_count += count_latin_letters(buffer);
            if (buffer[len - 1] == '\n') {
                fprintf(response_file, "%d\n", line_count);
                line_count = 0;
                in_line = 0;
            }
        } else {
            line_count = count_latin_letters(buffer);
            if (buffer[len - 1] != '\n') {
                in_line = 1;
            } else {
                fprintf(response_file, "%d\n", line_count);
                line_count = 0;
            }
        }
    }

    if (in_line) {
        fprintf(response_file, "%d\n", line_count);
    }

    fclose(input_file);
    fclose(response_file);
    return OK;
}

int count_number_of_characters(const char *str) {
    if (str == NULL)
        return INVALID_INPUT;
    int count = 0;
    while (*str) {
        if (!isalpha(*str) && !isdigit(*str) && *str != ' ') {
            count++;
        }
        str++;
    }
    return count;
}

enum Errors count_number_of_different_characters(const char* input_file_name, const char* response_file_name){
    if (input_file_name == NULL || response_file_name == NULL)
        return INVALID_INPUT;
    FILE *input_file = fopen(input_file_name, "r");
    if (input_file == NULL)
        return INVALID_INPUT;

    FILE *response_file = fopen(response_file_name, "w");
    if (response_file == NULL){
        fclose(input_file);
        return INVALID_INPUT;
    }

    int line_count = 0;
    int in_line = 0; 
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), input_file) != NULL) {
        size_t len = strlen(buffer);
        if (in_line) {
            line_count += count_number_of_characters(buffer);
            if (buffer[len - 1] == '\n') {
                fprintf(response_file, "%d\n", line_count);
                line_count = 0;
                in_line = 0;
            }
        } else {
            line_count = count_number_of_characters(buffer);
            if (buffer[len - 1] != '\n') {
                in_line = 1;
            } else {
                fprintf(response_file, "%d\n", line_count);
                line_count = 0;
            }
        }
    }

    if (in_line) {
        fprintf(response_file, "%d\n", line_count);
    }

    fclose(input_file);
    fclose(response_file);
    return OK;
}

enum Errors replacing_characters_to_ASCII_code(const char* input_file_name, const char* response_file_name){
    if (input_file_name == NULL || response_file_name == NULL)
        return INVALID_INPUT;
    FILE *input_file = fopen(input_file_name, "r");
    if (input_file == NULL)
        return INVALID_INPUT;

    FILE *response_file = fopen(response_file_name, "w");
    if (response_file == NULL){
        fclose(input_file);
        return INVALID_INPUT;
    }

    int c;
    while ((c = fgetc(input_file)) != EOF) {
        if (!isdigit(c)) {
            fprintf(response_file, "%X", c);
        } else {
            fputc(c, response_file);
        }
    }

    fclose(input_file);
    fclose(response_file);
    return OK;
}