#include "main.h"

int sum(int num1, int num2)
{
    int res = 0, carry = 0;
    res = num1 ^ num2;
    carry = (num1 & num2) << 1;
    while (carry)
    {
        int tmp = res;
        res = res ^ carry;
        carry = (tmp & carry) << 1;
    }
    return res;
}

enum Errors convert_to_base(const int base, int num, char **result)
{
    if (!result || base < 2 || base > 32)
        return INVALID_INPUT;
    int is_neg = 0;
    if (num < 0) {
        is_neg = 1;
        num = sum(~num, 1);
    }

    int base_pow = 0, base_copy = base;
    while (base_copy != 1) {
        base_pow = sum(base_pow, 1);
        base_copy = base_copy >> 1;
    }

    if (num == 0) {
        *result = (char*)malloc(2);
        if (!*result)
            return INVALID_MEMORY;
        (*result)[0] = '0';
        (*result)[1] = '\0';
        return OK;
    }

    int num_pow = 0, num_copy = num;
    while (num_copy != 0) {
        num_pow = sum(num_pow, 1);
        num_copy = num_copy >> base_pow;
    }
    
    char* base_str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned int mask = ~(~0U << base_pow);
    if (is_neg)
        num_pow = sum(num_pow, 1);
    *result = (char*)malloc(sum(num_pow, 1));
    if (!*result)
        return INVALID_MEMORY;

    int count = num_pow;
    (*result)[count] = '\0';
    while (num != 0)
    {
        count = sum(count, -1);
        (*result)[count] = base_str[num & mask];
        num = num >> base_pow;
    }
    
    if (is_neg){
        count = sum(count, -1);
        (*result)[count] = '-';
    }

    return OK;
}