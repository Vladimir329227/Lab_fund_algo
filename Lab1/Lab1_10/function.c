#include "main.h"

enum Errors convertToDecimal(const char *str, int base, long long int* result) {
    if (!str || !result)
        return INVALID_INPUT;
    *result = 0;
    int i = 0;
    int sign = 1;

    if (str[i] == '-') {
        sign = -1;
        i++;
    }

    while (str[i] != '\0') {
        int digit;
        if (isdigit(str[i]) && str[i] - '0' < base) {
            digit = str[i] - '0';
        } else if (isalpha(str[i]) && str[i] - 'A' + 10 < base) {
            digit = str[i] - 'A' + 10;
        } else {    
            return INVALID_INPUT;
        }
        *result = *result * base + digit;
        i++;
    }

    *result *= sign;
    return OK;
}

enum Errors convertToBase(const long long int num, int base, char *result) {
    if (!result)
        return INVALID_INPUT;
    

    int index = 0;
    int sign = 1;
    long long int num_t = llabs(num);

    do {
        int digit = num_t % base;
        result[index++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
        num_t /= base;
    } while (num_t > 0);

    if (sign == -1) {
        result[index++] = '-';
    }

    result[index] = '\0';

    for (int i = 0; i < index / 2; i++) {
        char temp = result[i];
        result[i] = result[index - i - 1];
        result[index - i - 1] = temp;
    }
    return OK;
}