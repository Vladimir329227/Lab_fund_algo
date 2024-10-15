#include "main.h"

enum Errors is_valid_flag(const char *str)
{
    if (str == NULL)
        return INVALID_INPUT;
    if ((str[0] == '-' || str[0] == '/') && str[2] == '\0')
        return OK;
    return INVALID_INPUT;
}

enum Errors my_strlen(const char *str, int* result)
{
    if (str == NULL || result == NULL)
        return INVALID_INPUT;
    *result = 0;
    while (str[*result] != '\0')
    {
        (*result)++;
        if (*result >= pow(10,7))
            return INVALID_INPUT;
    }

    return OK;
}

enum Errors my_reversed(const char *str, char **result)
{
    if (str == NULL)
        return INVALID_INPUT;
    
    int size_str;
    if (my_strlen(str, &size_str) != OK)
        return INVALID_INPUT;
    
    *result = (char *) malloc(size_str * sizeof(char));
    if (!*result)
        return INVALID_MEMORY;

    for (int i = 0; i < size_str; i++)
        (*result)[i] = str[size_str - i - 1];
    (*result)[size_str] = '\0';

    return OK;
}

enum Errors my_capitalize(const char *str, char **result)
{
    if (str == NULL)
        return INVALID_INPUT;
    
    int size_str;
    if (my_strlen(str, &size_str) != OK)
        return INVALID_INPUT;
    
    *result = (char *) malloc(size_str * sizeof(char));
    if (!*result)
        return INVALID_MEMORY;

    for (int i = 0; i < size_str; i++){
        if (i % 2 == 0)
            (*result)[i] = str[i];
        else{
            if ('a' <= str[i] && str[i] <= 'z') 
                (*result)[i] = str[i] + 'A' - 'a';
            else
                (*result)[i] = str[i];
        }
    }
    (*result)[size_str] = '\0';
    
    return OK;
}

enum Errors my_nedo_sort(const char *str, char **result)
{
    if (str == NULL)
        return INVALID_INPUT;
    
    int size_str;
    if (my_strlen(str, &size_str) != OK)
        return INVALID_INPUT;
    
    *result = (char *) malloc(size_str * sizeof(char));
    if (!*result)
        return INVALID_MEMORY;


    int cur_sim = 0;
    for (int i = 0; i < size_str; i++){
        if ('0' <= str[i] && str[i] <= '9') {
            (*result)[cur_sim] = str[i];
            cur_sim++;
        }
    }
    for (int i = 0; i < size_str; i++){
        if (('a' <= str[i] && str[i] <= 'z') || ('A' <= str[i] && str[i] <= 'Z')) {
            (*result)[cur_sim] = str[i];
            cur_sim++;
        }
    }
    for (int i = 0; i < size_str; i++){
        if (!('0' <= str[i] && str[i] <= '9') && !(('a' <= str[i] && str[i] <= 'z') || ('A' <= str[i] && str[i] <= 'Z'))) {
            (*result)[cur_sim] = str[i];
            cur_sim++;
        }
    }
    (*result)[size_str] = '\0';
    
    return OK;
}

enum Errors convert_str_to_int(const char *str, long long int * result, int base)
{
    char *endptr;
    *result = strtoll(str, &endptr, base);

    if (*result == LLONG_MAX || *result == LLONG_MIN)
        return INVALID_INPUT;
    else if (*endptr != '\0') 
        return INVALID_INPUT;

    return OK;
}

enum Errors is_equal(const char *str1, const char *str2, int* rez)
{
    if (str1 == NULL || str2 == NULL || rez == NULL)
        return INVALID_INPUT;
    int size_str1, size_str2;
    *rez = 1;

    if (my_strlen(str1, &size_str1) != OK || my_strlen(str2, &size_str2) != OK)
        return INVALID_INPUT;
    if (size_str1 != size_str2)
        *rez = 0;
    else{
        for (int i = 0; i < size_str1; i++)
        {
            if (str1[i] != str2[i]){
                *rez = 0;
                break;
            }
        }
    }
        
    return OK;
}

enum Errors my_concotenation(char **str, char **result, int count_str, long long int seed)
{
    if (str == NULL)
        return INVALID_INPUT;
    
    int size_str = 0, cur_size;
    for (int i = 0; i < count_str; i++)
    {
        if (my_strlen(str[i], &cur_size) != OK)
            return INVALID_INPUT;
        size_str += cur_size;
    }
    
    *result = (char *) malloc(size_str * sizeof(char));
    if (!*result)
        return INVALID_MEMORY;

    srand(seed);
    int rand_num, cur_count_str = 0, cur_size_str = 0;
    int* in_str_conc = (int *) malloc(count_str * sizeof(int));
    int is_nam_in_mas = 0;

    while (cur_count_str != count_str)
    {
        rand_num = rand() % count_str;
        do
        {
            is_nam_in_mas = 0;
            for(int o = 0; o < cur_count_str; o++){
                if (in_str_conc[o] == rand_num){
                    is_nam_in_mas = 1;
                }
            }
            if (is_nam_in_mas == 1)
                rand_num = (rand_num + 1) % count_str;
        }while (is_nam_in_mas != 0);
        
        

        if (is_nam_in_mas == 0){
            in_str_conc[cur_count_str] = rand_num;
            cur_count_str++;
            if (my_strlen(str[rand_num], &cur_size) != OK)
                return INVALID_INPUT;
            for (int o = 0; o < cur_size; o++)
            {
                (*result)[cur_size_str] = str[rand_num][o];
                cur_size_str++;
            }
        }
    }

    (*result)[size_str] = '\0';
    
    return OK;
}
