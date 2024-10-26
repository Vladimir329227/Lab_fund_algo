#include "main.h"

enum Errors charToDigit(char c, int base, int* result) {
    if (!result)
        return INVALID_INPUT;

    if (isdigit(c)) {
        if (c - '0' < base) {
            *result = c - '0';
            return OK;
        } else
            return INVALID_INPUT;
    } else if (isalpha(c)) {
        if (c - 'a' + 10 < base && c - 'a' + 10 > 0) {
            *result = c - 'a' + 10;
            return OK;
        } else
            return INVALID_INPUT;
        return tolower(c) - 'a' + 10;
    }

    return INVALID_INPUT;
}

enum Errors digitToChar(int digit, char* result) {
    if (!result)
        return INVALID_INPUT;
    if (digit < 10) {
        *result = '0' + digit;
        return OK;
    } else {
        *result = 'a' + digit - 10;
        if (*result < 'a' || *result > 'z')
            return INVALID_INPUT;
        return OK;
    }
    
}

enum Errors addInBase(int base, const char* num1, const char* num2, char** result) {
    if (!result || !num1 || !num2) 
        return INVALID_INPUT;

    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxLen = (len1 > len2) ? len1 : len2;
    int carry = 0;
    *result = (char*)malloc(maxLen + 2); // +2 для возможного переноса и нуль-терминатора

    if (!*result) 
        return INVALID_MEMORY;

    int digit1, digit2;
    for (int i = 0; i < maxLen + 1; i++) {
        if (i < len1){
            if (charToDigit(num1[len1 - 1 - i], base, &digit1) != OK)
                return INVALID_INPUT;
        }
        else
            digit1 = 0;
        if (i < len2){
            if (charToDigit(num2[len2 - 1 - i], base, &digit2) != OK)
                return INVALID_INPUT;
        }
        else
            digit2 = 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / base;
        if (digitToChar(sum % base, &((*result)[maxLen - i])) != OK) {
            free(*result);
            return INVALID_INPUT;
        }
    }

    int start = 0;
    while (start < maxLen + 1 && (*result)[start] == '0') {
        start++;
    }

    memmove(*result, *result + start, maxLen + 1 - start);
    (*result)[maxLen + 1 - start] = '\0';

    return OK;
}

enum Errors sumInBase(char** result, int base, int count, ...) {
    if (count == 0) {
        *result = NULL;
        return OK;
    }

    if (base < 2 || base > 36 || !result) 
        return INVALID_INPUT;
    va_list args;
    va_start(args, count);

    const char* firstNum = va_arg(args, const char*);
    *result = (char*)malloc(strlen(firstNum) + 1);
    if (!*result) {
        va_end(args);
        return INVALID_MEMORY;
    }
    strcpy(*result, firstNum);

    char* temp, *next;
    enum Errors error;
    for (int i = 1; i < count; i++) {
        next = va_arg(args, char*);
        error = addInBase(base, *result, next, &temp);
        if (error != OK) {
            free(*result);
            va_end(args);
            return error;
        }
        free(*result);
        *result = temp;
    }

    va_end(args);
    return OK;
}