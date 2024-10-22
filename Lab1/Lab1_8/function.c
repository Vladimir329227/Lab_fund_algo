#include "main.h"

int get_min_base(const char *number) {
    int max_digit = 0;
    int i = 0;
    char c;
    int digit;


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
    int exponent = 0, cur_exp = 0;
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
        if ( digit * base > LONG_MAX / *result / base)
            return INVALID_INPUT;

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
                if (exp_value > INT_MAX / 10 - (number[i] - '0'))
                    return INVALID_INPUT;
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
        cur_exp = pow(base, exponent);
        if (*result > DBL_MAX / cur_exp)
            return INVALID_INPUT;
        *result = *result * cur_exp;
    }

    *result *= sign;

    if (strlen(number) != (size_t)(i - space))
        return INVALID_INPUT;

    return OK;
}

int is_file_identical(const char *path1, const char *path2) {
    char resolved_path1[MAX_PATH];
    char resolved_path2[MAX_PATH];

    if (GetFullPathName(path1, MAX_PATH, resolved_path1, NULL) == 0) {
        return 0;
    }

    if (GetFullPathName(path2, MAX_PATH, resolved_path2, NULL) == 0) {
        return 0;
    }

    //printf("%s\n%s\n",resolved_path1, resolved_path2);

    return strcmp(resolved_path1, resolved_path2) == 0;
}

enum Errors process_files(const char *input_path, const char *output_path) {
    if (!input_path || !output_path)
        return INVALID_INPUT;

    if (is_file_identical(input_path, output_path))
        return INVALID_INPUT;

    FILE *input_file = fopen(input_path, "r");
    FILE *output_file = fopen(output_path, "w");

    if (!input_file || !output_file){
        if (input_file) fclose(input_file);
        if (output_file) fclose(output_file);
        return ERROR_OPEN_FILE;
    }

    char buffer[MAX_LEN_NAMBER];
    int buffer_index = 0, c, min_base;
    double decimal_value;

    while ((c = fgetc(input_file)) != EOF) {
        if (isspace(c)) {
            if (buffer_index > 0) {
                buffer[buffer_index] = '\0';
                min_base = get_min_base(buffer);
                if (convert_to_decimal(buffer, min_base, &decimal_value) == OK)
                    fprintf(output_file, "%s %d %.10f\n", buffer, min_base, decimal_value);
                buffer_index = 0;
            }
        } else {
            if (buffer_index >= MAX_LEN_NAMBER - 1){
                return INVALID_INPUT;
            }
            buffer[buffer_index++] = c;
        }
    }
    
    buffer[buffer_index] = '\0';
    min_base = get_min_base(buffer);
    if (buffer_index != 0 && convert_to_decimal(buffer, min_base, &decimal_value) == OK)
        fprintf(output_file, "%s %d %.10f\n", buffer, min_base, decimal_value);
    buffer_index = 0;

    fclose(input_file);
    fclose(output_file);
    return OK;
}