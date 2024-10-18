#include "main.h"

long long int hash_string(const char *str, int len, int begin) {
    long long int hash = 0;
    for (int i = 0; i < len; i++) {
        hash = (hash * BASE + str[(begin + i) % len]) % HASH_SPREAD;
    }
    return hash;
}

enum Errors count_substring_in_file(int* result, const char *filename, long long int str_hash, int substring_len) {
    if (!filename)
        return INVALID_INPUT; 

    FILE *file = fopen(filename, "r");
    if (!file) 
        return ERROR_OPEN_FILE;

    char buffer[substring_len];
    int buffer_index = 0, c;
    long long int current_hash;
    while ((c = fgetc(file)) != EOF) {
        buffer[buffer_index] = c;
        buffer_index = (buffer_index + 1) % substring_len;
        current_hash = hash_string(buffer, substring_len, buffer_index);
        if (current_hash == str_hash)
            *result += 1;
        
    }
    
    fclose(file);

    return OK;
}

enum Errors search_substring_in_file(int** result, int* cur_elem, const char *filename, long long int str_hash, int substring_len) {
    if (!filename || !result || !cur_elem)
        return INVALID_INPUT; 

    FILE *file = fopen(filename, "r");
    if (!file) 
        return ERROR_OPEN_FILE;

    char buffer[substring_len];
    int buffer_index = 0, c;
    long long int current_hash;
    int line = 1, simbol = 0, is_start = 0;

    while ((c = fgetc(file)) != EOF) {
        if (is_start + 1 < substring_len){
            is_start++;
        }
        else if(buffer[buffer_index] == '\n'){
            line++;
            simbol = 0;
        }
        else{
            simbol++;
        }

        buffer[buffer_index] = c;
        buffer_index = (buffer_index + 1) % substring_len;
        current_hash = hash_string(buffer, substring_len, buffer_index);
        if (current_hash == str_hash){
            printf("%i %i\n", line, simbol);
            (*result)[*cur_elem] = line;
            (*cur_elem)++;
            (*result)[*cur_elem] = simbol;
            (*cur_elem)++;
        }
        
    }
    
    fclose(file);

    return OK;
}

enum Errors find_word(int** result, int* cur_elem, const char* str, const int count, ...) {
    if (count <= 0 || !result || !str)
        return INVALID_INPUT; 

    long long int str_hash = hash_string(str, strlen(str), 0);

    va_list args;
    va_start(args, count);

    int count_word = 0;

    enum Errors err; 

    for (int i = 0; i < count; i++) {
        const char *filename = va_arg(args, const char *);
        err = count_substring_in_file(&count_word, filename, str_hash, strlen(str));  
        if (err != OK)
            return err;
    }

    (*result) = (int*)malloc(count_word * 2 * sizeof(int));
    if (!*result)
        return INVALID_MEMORY;
    *cur_elem = 0;

    va_end(args);
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        const char *filename = va_arg(args, const char *);
        printf("%s\n",filename);
        err = search_substring_in_file(result, cur_elem, filename, str_hash, strlen(str));  
        if (err != OK){
            free(*result);
            return err;
        }
    }

    va_end(args);

    return OK;
}