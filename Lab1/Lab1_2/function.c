#include "main.h"

enum Errors convert_str_to_int(const char *str, long long int * result, int base)
{
    char *endptr;
    *result = strtoll(str, &endptr, base);

    if (errno == ERANGE && (*result == LLONG_MAX || *result == LLONG_MIN))
        return INVALID_INPUT;
    else if (*endptr != '\0') 
        return INVALID_INPUT;

    return OK;
}
