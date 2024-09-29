#include "main.h"

int get_min_base(const char *number) {
    int max_digit = 0;
    int i = 0;
    char c;
    int digit;


    // Пропускаем пробелы и определяем знак
    while (number[i] == ' ' || number[i] == '\t' || number[i] == '\n') i++;
    if (number[i] == '-' || number[i] == '+') i++;

    // Обрабатываем число до экспоненциальной части или дробной части
    while (number[i] != '\0' && !((number[i] == 'E' || number[i] == 'e') && (number[i+1] == '+' || number[i+1] == '-'))) {
        c = number[i];
        if (isdigit(c)) {
            digit = c - '0';
        } else if (isalpha(c)) {
            digit = tolower(c) - 'a' + 10;
        } else {
            break;
        }
        if (digit > max_digit) max_digit = digit;
        i++;
        if (number[i] == '.' || number[i] == ',')
            i++;
    }


    
    // Обрабатываем дробную часть
    if (number[i] == '.' || number[i] == ',') {
        i++;
        while (number[i] != '\0' && !((number[i] == 'E' || number[i] == 'e') && (number[i+1] == '+' || number[i+1] == '-'))) {
            c = number[i];
            if (isdigit(c)) {
                digit = c - '0';
            } else if (isalpha(c)) {
                digit = tolower(c) - 'a' + 10;
            } else {
                break;
            }
            if (digit > max_digit) max_digit = digit;
            i++;
        }
    }

    return max_digit + 1;
}

enum Errors convert_to_decimal(const char *number, int base,double* result) {
    *result = 0.0;
    int exponent = 0;
    int sign = 1;
    int i = 0, space = 0;
    int fractional_part = 0;
    double fractional_value = 0.0;

    while (number[i] == ' ' || number[i] == '\t' || number[i] == '\n') space++;
    i = space;
    if (number[i] == '-') {
        sign = -1;
        i++;
    } else if (number[i] == '+') {
        i++;
    }

    char c;
    int digit;

    while (number[i] != '\0' && !((number[i] == 'E' || number[i] == 'e') && (number[i+1] == '+' || number[i+1] == '-')) && number[i] != '.' && number[i] != ',') {
        c = number[i];
        if (isdigit(c)) {
            digit = c - '0';
        } else if (isalpha(c)) {
            digit = tolower(c) - 'a' + 10;
        } else {
            break;
        }
        *result = *result * base + digit;
        i++;
    }


    double fractional_base;
    // Обрабатываем дробную часть
    if (number[i] == '.' || number[i] == ',') {
        fractional_part = 1;
        i++;
        fractional_base = base;
        while (number[i] != '\0' && !((number[i] == 'E' || number[i] == 'e') && (number[i+1] == '+' || number[i+1] == '-'))) {
            c = number[i];
            if (isdigit(c)) {
                digit = c - '0';
            } else if (isalpha(c)) {
                digit = tolower(c) - 'a' + 10;
            } else {
                break;
            }
            fractional_value += digit / fractional_base;
            fractional_base *= base;
            i++;
        }
    }

    int exp_sign = 1;
    int exp_value = 0;
    // Обрабатываем экспоненциальную часть
    if (number[i] == 'E' || number[i] == 'e') {
        i++;
        if (number[i] == '-' || number[i] == '+') {
            if (number[i] == '-') {
                exp_sign = -1;
                i++;
            } else if (number[i] == '+') {
                i++;
            }
            while (isdigit(number[i])) {
                exp_value = exp_value * 10 + (number[i] - '0');
                i++;
            }
            exponent = exp_value * exp_sign;
        } else {
            // Если после 'E' или 'e' нет знака, то это простая цифра
            *result = *result * base + (tolower(number[i - 1]) - 'a' + 10);
        }
    }

    if (fractional_part) {
        *result += fractional_value;
    }

    if (exponent != 0) {
        *result = *result * pow(base, exponent);
    }

    *result *= sign;

    if (strlen(number) != (size_t)(i - space))
        return INVALID_INPUT;

    return OK;
}

enum Errors process_files(const char *input_path, const char *output_path) {
    if (!input_path || !output_path){
        return INVALID_INPUT;
    }

    FILE *input_file = fopen(input_path, "r");
    FILE *output_file = fopen(output_path, "w");

    if (!input_file || !output_file){
        if (input_file) fclose(input_file);
        if (output_file) fclose(output_file);
        return ERROR_OPEN_FILE;
    }

    char buffer[1024];
    double decimal_value;
    int min_base;
    while (fgets(buffer, sizeof(buffer), input_file) != NULL) {
        char *token = strtok(buffer, " \t\n");
        while (token != NULL) {
            min_base = get_min_base(token);
            if (convert_to_decimal(token, min_base, &decimal_value) == OK)
                fprintf(output_file, "%s %d %.10f\n",token , min_base, decimal_value);
            token = strtok(NULL, " \t\n");
        }
        free(token);
    }

    fclose(input_file);
    fclose(output_file);
    return OK;
}