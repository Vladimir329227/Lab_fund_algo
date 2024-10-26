#include "main.h"

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
    int prev = 0;

    while (*s) {
        int curr = values[(unsigned char)*s];
        result += curr;
        if (curr > prev) {
            result -= 2 * prev;
        }
        prev = curr;
        s++;
    }

    return result;
}

unsigned int zeckendorfToInt(const char *s) {
    unsigned int result = 0;
    unsigned int fib1 = 1, fib2 = 1;

    while (*s) {
        if (*s == '1') {
            result += fib2;
        }
        unsigned int nextFib = fib1 + fib2;
        fib1 = fib2;
        fib2 = nextFib;
        s++;
    }

    return result;
}

int customStrToInt(const char *s, int base) {
    int result = 0;
    while (*s) {
        int value = 0;
        if (*s >= '0' && *s <= '9') {
            value = *s - '0';
        } else if (*s >= 'a' && *s <= 'z') {
            value = *s - 'a' + 10;
        } else if (*s >= 'A' && *s <= 'Z') {
            value = *s - 'A' + 10;
        }
        result = result * base + value;
        s++;
    }
    return result;
}

int overfscanf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);

    int count = 0;
    while (*format) {
        if (*format == '%') {
            format++;
            if (*format == 'R' && *(format + 1) == 'o') {
                char buffer[256];
                fscanf(stream, "%s", buffer);
                int *value = va_arg(args, int *);
                *value = romanToInt(buffer);
                count++;
                format += 2;
            } else if (*format == 'Z' && *(format + 1) == 'r') {
                char buffer[256];
                fscanf(stream, "%s", buffer);
                unsigned int *value = va_arg(args, unsigned int *);
                *value = zeckendorfToInt(buffer);
                count++;
                format += 2;
            } else if (*format == 'C' && *(format + 1) == 'v') {
                int base = va_arg(args, int);
                if (base < 2 || base > 36) {
                    base = 10;
                }
                char buffer[256];
                fscanf(stream, "%s", buffer);
                int *value = va_arg(args, int *);
                *value = customStrToInt(buffer, base);
                count++;
                format += 2;
            } else if (*format == 'C' && *(format + 1) == 'V') {
                int base = va_arg(args, int);
                if (base < 2 || base > 36) {
                    base = 10;
                }
                char buffer[256];
                fscanf(stream, "%s", buffer);
                int *value = va_arg(args, int *);
                *value = customStrToInt(buffer, base);
                count++;
                format += 2;
            } else {
                char buffer[256];
                fscanf(stream, "%s", buffer);
                va_arg(args, void *);
                count++;
            }
        } else {
            format++;
        }
    }

    va_end(args);
    return count;
}

// Функция oversscanf
int oversscanf(const char *format, ...) {
    char input[256];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0; // Ошибка чтения
    }

    va_list args;
    va_start(args, format);

    int count = 0;
    const char *ptr = input;
    while (*format) {
        if (*format == '%') {
            format++;
            if (*format == 'R' && *(format + 1) == 'o') {
                char buffer[256];
                sscanf(ptr, "%s", buffer);
                int *value = va_arg(args, int *);
                *value = romanToInt(buffer);
                count++;
                format += 2;
                ptr += strlen(buffer);
            } else if (*format == 'Z' && *(format + 1) == 'r') {
                char buffer[256];
                sscanf(ptr, "%s", buffer);
                unsigned int *value = va_arg(args, unsigned int *);
                *value = zeckendorfToInt(buffer);
                count++;
                format += 2;
                ptr += strlen(buffer);
            } else if (*format == 'C' && *(format + 1) == 'v') {
                int base = va_arg(args, int);
                if (base < 2 || base > 36) {
                    base = 10;
                }
                char buffer[256];
                sscanf(ptr, "%s", buffer);
                int *value = va_arg(args, int *);
                *value = customStrToInt(buffer, base);
                count++;
                format += 2;
                ptr += strlen(buffer);
            } else if (*format == 'C' && *(format + 1) == 'V') {
                int base = va_arg(args, int);
                if (base < 2 || base > 36) {
                    base = 10;
                }
                char buffer[256];
                sscanf(ptr, "%s", buffer);
                int *value = va_arg(args, int *);
                *value = customStrToInt(buffer, base);
                count++;
                format += 2;
                ptr += strlen(buffer);
            } else {
                // Обработка стандартных флагов
                char format_spec[3] = "% ";
                format_spec[1] = *format;
                format_spec[2] = '\0';
                if (sscanf(ptr, format_spec, va_arg(args, void *)) == 1) {
                    count++;
                }
                while (*ptr && !isspace((unsigned char)*ptr)) {
                    ptr++;
                }
                while (*ptr && isspace((unsigned char)*ptr)) {
                    ptr++;
                }
            }
        } else {
            format++;
        }
    }

    va_end(args);
    return count;
}