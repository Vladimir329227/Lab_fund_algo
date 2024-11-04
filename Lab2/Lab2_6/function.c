#include "main.h"

// Функция для преобразования римских цифр в целое число
int romanToInt(const char *s) {
    int values[256] = {0};
    values['I'] = 1;
    values['V'] = 5;
    values['X'] = 10;
    values['L'] = 50;
    values['C'] = 100;
    values['D'] = 500;
    values['M'] = 1000;

    int result = 0;
    int prevValue = 0;

    while (*s) {
        int currValue = values[(unsigned char)*s];
        if (currValue > prevValue) {
            result += currValue - 2 * prevValue;
        } else {
            result += currValue;
        }
        prevValue = currValue;
        s++;
    }

    return result;
}

// Функция для преобразования цекендорфова представления в целое число
unsigned int zeckendorfToInt(const char *s) {
    unsigned int result = 0;
    unsigned int fib1 = 1, fib2 = 1;

    while (*s) {
        if (*s == '1') {
            result += fib1;
        }
        unsigned int nextFib = fib1 + fib2;
        fib1 = fib2;
        fib2 = nextFib;
        s++;
    }

    return result;
}

// Функция для преобразования строки в целое число с заданным основанием
int strToIntWithBase(const char *s, int base) {
    int result = 0;
    while (*s) {
        int value;
        if (*s >= '0' && *s <= '9') {
            value = *s - '0';
        } else if (*s >= 'a' && *s <= 'z') {
            value = *s - 'a' + 10;
        } else if (*s >= 'A' && *s <= 'Z') {
            value = *s - 'A' + 10;
        } else {
            break;
        }
        result = result * base + value;
        s++;
    }
    return result;
}

// Функция overfscanf
int overfscanf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);

    int count = 0;
    const char *fmt = format;
    char buffer[256];
    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            if (*fmt == 'R' && *(fmt + 1) == 'o') {
                if (fscanf(stream, "%255s", buffer) == 1) {
                    int *value = va_arg(args, int *);
                    *value = romanToInt(buffer);
                    count++;
                }
                fmt += 2;
            } else if (*fmt == 'Z' && *(fmt + 1) == 'r') {
                if (fscanf(stream, "%255s", buffer) == 1) {
                    unsigned int *value = va_arg(args, unsigned int *);
                    *value = zeckendorfToInt(buffer);
                    count++;
                }
                fmt += 2;
            } else if (*fmt == 'C' && *(fmt + 1) == 'v') {
                int *base = va_arg(args, int *);
                if (*base < 2 || *base > 36) {
                    *base = 10;
                }
                if (fscanf(stream, "%255s", buffer) == 1) {
                    int *value = va_arg(args, int *);
                    *value = strToIntWithBase(buffer, *base);
                    count++;
                }
                fmt += 2;
            } else if (*fmt == 'C' && *(fmt + 1) == 'V') {
                int *base = va_arg(args, int *);
                if (*base < 2 || *base > 36) {
                    *base = 10;
                }
                if (fscanf(stream, "%255s", buffer) == 1) {
                    int *value = va_arg(args, int *);
                    *value = strToIntWithBase(buffer, *base);
                    count++;
                }
                fmt += 2;
            } else {
                va_list args_copy;
                va_copy(args_copy, args);
                if (fscanf(stream, fmt, args_copy) == 1) {
                    count++;
                }
                va_end(args_copy);
                while (*fmt && *fmt != '%') fmt++;
            }
        } else {
            fscanf(stream, "%c", buffer);
            printf("%c %c\n", *fmt, buffer[0]);
            fmt++;
        }
    }

    va_end(args);
    return count;
}

int oversscanf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);

    int count = 0;
    const char *fmt = format;
    char* copy_str = str;
    char buffer[256];

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            if (*fmt == 'R' && *(fmt + 1) == 'o') {
                if (sscanf(str, "%255s", buffer) == 1) {
                    int *value = va_arg(args, int *);
                    *value = romanToInt(buffer);
                    count++;
                }
                fmt += 2;
                copy_str += strlen(buffer);
            } else if (*fmt == 'Z' && *(fmt + 1) == 'r') {
                if (sscanf(str, "%255s", buffer) == 1) {
                    unsigned int *value = va_arg(args, unsigned int *);
                    *value = zeckendorfToInt(buffer);
                    count++;
                }
                fmt += 2;
                copy_str += strlen(buffer);
            } else if (*fmt == 'C' && *(fmt + 1) == 'v') {
                int *base = va_arg(args, int *);
                if (*base < 2 || *base > 36) {
                    *base = 10;
                }
                if (sscanf(str, "%255s", buffer) == 1) {
                    int *value = va_arg(args, int *);
                    *value = strToIntWithBase(buffer, *base);
                    count++;
                }
                fmt += 2;
                copy_str += strlen(buffer);
            } else if (*fmt == 'C' && *(fmt + 1) == 'V') {
                int *base = va_arg(args, int *);
                if (*base < 2 || *base > 36) {
                    *base = 10;
                }
                if (sscanf(str, "%255s", buffer) == 1) {
                    int *value = va_arg(args, int *);
                    *value = strToIntWithBase(buffer, *base);
                    count++;
                }
                fmt += 2;
                copy_str += strlen(buffer);
            } else {
                va_list args_copy;
                va_copy(args_copy, args);
                if (sscanf(str, fmt, args_copy) == 1) {
                    count++;
                }
                va_end(args_copy);
                while (*fmt && *fmt != '%') fmt++;
            }
        } else {
            sscanf(str, "%c", buffer);
            printf(str, "%c %c\n", *fmt, buffer[0]);
            fmt++;
        }
    }

    va_end(args);
    return count;
}