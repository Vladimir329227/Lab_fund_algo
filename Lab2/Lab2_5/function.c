#include "main.h"

enum Errors to_roman(int num, char *buffer) {
    if (num <= 0 || num >= 4000 || !buffer)
        return INVALID_INPUT;
    const char *roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    buffer[0] = '\0';
    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            strcat(buffer, roman[i]);
            num -= values[i];
        }
    }
    return OK;
}

void generate_fibonacci(unsigned int *fib_sequence, unsigned int n) {
    fib_sequence[0] = 1;
    fib_sequence[1] = 2;
    int i = 2;
    while (fib_sequence[i - 1] <= n) {
        fib_sequence[i] = fib_sequence[i - 1] + fib_sequence[i - 2];
        i++;
    }
    fib_sequence[i-1] = 0;
}

enum Errors to_zeckendorf(unsigned int num, char *buffer) {
    if (!buffer)
        return INVALID_INPUT;
    unsigned int fib_sequence[100];

    if (num == 0){
        buffer[1] = '1';
        buffer[0] = '0';
        buffer[2] = '\0';
        return OK;
    }
    if (num == 1){
        buffer[0] = '1';
        buffer[1] = '1';
        buffer[2] = '\0';
        return OK;
    }

    generate_fibonacci(fib_sequence, num);

    buffer[0] = '\0';

    int i = 0;
    while (fib_sequence[i] != 0) {
        i++;
    }
    i--; 

    while (i >= 0) {
        if (num >= fib_sequence[i]) {
            num -= fib_sequence[i];
            strcat(buffer, "1");
        } else {
            strcat(buffer, "0");
        }
        i--;
    }

    strcat(buffer, "1"); 
    return OK;
}

enum Errors to_base(int num, int base, int uppercase, char *buffer) {
    if (!buffer)
        return INVALID_INPUT;
    buffer[0] = '\0';

    if (num == 0) {
        strcat(buffer, "0");
        return OK;
    }
    int is_negative = 0;
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    int index = 0, digit;
    while (num > 0) {
        digit = num % base;
        if (digit < 10) {
            buffer[index++] = '0' + digit;
        } else {
            buffer[index++] = 'a' + (digit - 10);
            if (uppercase) 
                buffer[index - 1] = toupper(buffer[index - 1]);
        }
        num /= base;
    }

    if (is_negative) {
        buffer[index++] = '-';
    }
    buffer[index] = '\0';

    char temp;
    for (int i = 0; i < index / 2; i++) {
        temp = buffer[i];
        buffer[i] = buffer[index - i - 1];
        buffer[index - i - 1] = temp;
    }
    return OK;
}


enum Errors from_base(const char *str, int base, int* result) {
    if (!result)
        return INVALID_INPUT;
    *result = 0;
    char c;
    int i = 0, is_otr = 1;

    if (str[0] == '-'){
        is_otr = -1;
        i++;
    }

    for (; str[i] != '\0'; i++) {
        c = str[i];
        if (*result > INT_MAX / base / base)
            return INVALID_INPUT;

        if (c >= '0' && c <= '9') {
            *result = *result * base + (c - '0');
        } else if (c >= 'a' && c <= 'z') {
            *result = *result * base + (c - 'a' + 10);
        } else if (c >= 'A' && c <= 'Z') {
            *result = *result * base + (c - 'A' + 10);
        } else{
            return INVALID_INPUT;
        }
    }

    *result *= is_otr;
    return OK;
}

enum Errors memory_dump(const void *data, size_t size, char *buffer) {
    if (!data || !buffer || size == 0)
        return INVALID_INPUT;
    
    const unsigned char *bytes = (const unsigned char *)data;
    buffer[0] = '\0';
    char byte_str[9];

    for (size_t i = 0; i < size; i++) {
        for (int j = 0; j < 8; j++) {
            byte_str[7 - j] = (bytes[i] & (1 << j)) ? '1' : '0';
        }
        byte_str[8] = '\0';
        strcat(buffer, byte_str);
        if (i < size - 1) {
            strcat(buffer, " ");
        }
    }
    return OK;
}

enum Errors overfprintf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = 0;
    char buffer[100];
    int num, base;
    unsigned int u_num;
    double d_num;
    float f_num;
    char *str;
    enum Errors err = OK;
    const char *fmt_start;
    size_t fmt_len;
    
    while (*format) {
        if (*format == '%') {
            format++;
            if (*format == 'R' && *(format + 1) == 'o') {
                num = va_arg(args, int);
                err = to_roman(num, buffer);
                if (err != OK)
                    break;
                result = fprintf(stream, "%s", buffer);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                format += 2;
            } else if (*format == 'Z' && *(format + 1) == 'r') {
                u_num = va_arg(args, unsigned int);
                err = to_zeckendorf(u_num, buffer);
                if (err != OK)
                    break;
                result = fprintf(stream, "%s", buffer);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                format += 2;
            } else if (*format == 'C' && *(format + 1) == 'v') {
                num = va_arg(args, int);
                base = va_arg(args, int);
                if (base < 2 || base > 36) base = 10;
                err = to_base(num, base, 0, buffer);
                if (err != OK)
                    break;
                result = fprintf(stream, "%s", buffer);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                format += 2;
            } else if (*format == 'C' && *(format + 1) == 'V') {
                num = va_arg(args, int);
                base = va_arg(args, int);
                if (base < 2 || base > 36) base = 10;
                err = to_base(num, base, 1, buffer);
                if (err != OK)
                    break;
                result = fprintf(stream, "%s", buffer);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                format += 2;
            } else if (*format == 't' && *(format + 1) == 'o') {
                str = va_arg(args, char *);
                base = va_arg(args, int);
                if (base < 2 || base > 36) base = 10;
                err = from_base(str, base, &num);
                if (err != OK)
                    break;
                result = fprintf(stream, "%d", num);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                format += 2;
            } else if (*format == 'T' && *(format + 1) == 'O') {
                str = va_arg(args, char *);
                base = va_arg(args, int);
                if (base < 2 || base > 36) base = 10;
                err = from_base(str, base, &num);
                if (err != OK)
                    break;
                result = fprintf(stream, "%d", num);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                format += 2;
            } else if (*format == 'm' && *(format + 1) == 'i') {
                num = va_arg(args, int);
                err = memory_dump(&num, sizeof(num), buffer);
                if (err != OK)
                    break;
                result = fprintf(stream, "%s", buffer);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                format += 2;
            } else if (*format == 'm' && *(format + 1) == 'u') {
                u_num = va_arg(args, unsigned int);
                err = memory_dump(&u_num, sizeof(u_num), buffer);
                if (err != OK)
                    break;
                result = fprintf(stream, "%s", buffer);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                format += 2;
            } else if (*format == 'm' && *(format + 1) == 'd') {
                d_num = va_arg(args, double);
                err = memory_dump(&d_num, sizeof(d_num), buffer);
                if (err != OK)
                    break;
                result = fprintf(stream, "%s", buffer);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                format += 2;
            } else if (*format == 'm' && *(format + 1) == 'f') {
                f_num = (float)va_arg(args, double);
                err = memory_dump(&f_num, sizeof(f_num), buffer);
                if (err != OK)
                    break;
                result = fprintf(stream, "%s", buffer);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                format += 2;
            } else if (*format == '%') {
                result += fprintf(stream, "%%");
                format++;
            } else {
                fmt_start = format - 1;
                while (*format && *format != '%') {
                    format++;
                }
                fmt_len = format - fmt_start;
                char fmt[fmt_len + 1];
                strncpy(fmt, fmt_start, fmt_len);
                fmt[fmt_len] = '\0';
                result = vfprintf(stream, fmt, args);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
            }
        } else {
            result = fprintf(stream, "%c", *format);
            if (result == -1){
                err = INVALID_INPUT;
                break;
            }
            format++;
        }
    }
    va_end(args);
    return err;
}

enum Errors oversprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = 0;
    char buffer[100];
    int num, base;
    unsigned int u_num;
    double d_num;
    float f_num;
    char *str_arg;
    enum Errors err = OK;
    const char *fmt_start;
    size_t fmt_len;

    while (*format) {
        if (*format == '%') {
            format++;
            if (*format == 'R' && *(format + 1) == 'o') {
                num = va_arg(args, int);
                err = to_roman(num, buffer);
                if (err != OK)
                    break;
                result = sprintf(str, "%s", buffer);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                str += strlen(buffer);
                format += 2;
            } else if (*format == 'Z' && *(format + 1) == 'r') {
                u_num = va_arg(args, unsigned int);
                err = to_zeckendorf(u_num, buffer);
                if (err != OK)
                    break;
                result = sprintf(str, "%s", buffer);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                str += strlen(buffer);
                format += 2;
            } else if (*format == 'C' && *(format + 1) == 'v') {
                num = va_arg(args, int);
                base = va_arg(args, int);
                if (base < 2 || base > 36) base = 10;
                err = to_base(num, base, 0, buffer);
                if (err != OK)
                    break;
                result = sprintf(str, "%s", buffer);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                str += strlen(buffer);
                format += 2;
            } else if (*format == 'C' && *(format + 1) == 'V') {
                num = va_arg(args, int);
                base = va_arg(args, int);
                if (base < 2 || base > 36) base = 10;
                err = to_base(num, base, 1, buffer);
                if (err != OK)
                    break;
                result = sprintf(str, "%s", buffer);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                str += strlen(buffer);
                format += 2;
            } else if (*format == 't' && *(format + 1) == 'o') {
                str_arg = va_arg(args, char *);
                base = va_arg(args, int);
                if (base < 2 || base > 36) base = 10;
                err = from_base(str_arg, base, &num);
                if (err != OK)
                    break;
                result = sprintf(str, "%d", num);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                str += strlen(str);
                format += 2;
            } else if (*format == 'T' && *(format + 1) == 'O') {
                str_arg = va_arg(args, char *);
                base = va_arg(args, int);
                if (base < 2 || base > 36) base = 10;
                err = from_base(str_arg, base, &num);
                if (err != OK)
                    break;
                result = sprintf(str, "%d", num);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                str += strlen(str);
                format += 2;
            } else if (*format == 'm' && *(format + 1) == 'i') {
                num = va_arg(args, int);
                err = memory_dump(&num, sizeof(num), buffer);
                if (err != OK)
                    break;
                result = sprintf(str, "%s", buffer);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                str += strlen(buffer);
                format += 2;
            } else if (*format == 'm' && *(format + 1) == 'u') {
                u_num = va_arg(args, unsigned int);
                err = memory_dump(&u_num, sizeof(u_num), buffer);
                if (err != OK)
                    break;
                result = sprintf(str, "%s", buffer);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                str += strlen(buffer);
                format += 2;
            } else if (*format == 'm' && *(format + 1) == 'd') {
                d_num = va_arg(args, double);
                err = memory_dump(&d_num, sizeof(d_num), buffer);
                if (err != OK)
                    break;
                result = sprintf(str, "%s", buffer);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                str += strlen(buffer);
                format += 2;
            } else if (*format == 'm' && *(format + 1) == 'f') {
                f_num = (float)va_arg(args, double);
                err = memory_dump(&f_num, sizeof(f_num), buffer);
                if (err != OK)
                    break;
                result = sprintf(str, "%s", buffer);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }
                str += strlen(buffer);
                format += 2;
            } else if (*format == '%') {
                result += sprintf(str, "%%");
                str++;
                format++;
            } else {
                fmt_start = format - 1;
                while (*format && *format != '%') {
                    format++;
                }
                fmt_len = format - fmt_start;
                char fmt[fmt_len + 1];
                strncpy(fmt, fmt_start, fmt_len);
                fmt[fmt_len] = '\0';
                result = vsprintf(str, fmt, args);
                if (result == -1){
                    err = INVALID_INPUT;
                    break;
                }


                str += strlen(str);
            }
        } else {
            result = sprintf(str, "%c", *format);
            if (result == -1){
                err = INVALID_INPUT;
                break;
            }
            str++;
            format++;
        }
    }

    va_end(args);
    return err;
}
