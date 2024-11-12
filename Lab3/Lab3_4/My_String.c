#include "main.h"

enum Errors createString(const char *str, String *new_str) {
    if (!new_str || !str)
        return INVALID_INPUT;    
    new_str->length = 0;
    while (str[new_str->length] != '\0')
        new_str->length++;
    new_str->data = (char *)malloc((new_str->length + 1) * sizeof(char));
    if (new_str->data == NULL) 
        return INVALID_MEMORY;
    for (int i = 0; i <= new_str->length; i++) 
        new_str->data[i] = str[i];
    return OK;
}

enum Errors deleteString(String *str) {
    if (!str)
        return INVALID_INPUT;
    if (str->data != NULL){
        free(str->data);
        str->data = NULL;           
    }
    str->length = 0;
    return OK;
}

int compareStrings(const String *str1, const String *str2) {
    if (str1->length != str2->length) 
        return str1->length - str2->length;
    for (int i = 0; i < str1->length; i++) 
        if (str1->data[i] != str2->data[i]) 
            return str1->data[i] - str2->data[i];
    return 0;
}

int areStringsEqual(const String *str1, const String *str2) {
    if (str1->length != str2->length)
        return 0;
    for (int i = 0; i < str1->length; i++)
        if (str1->data[i] != str2->data[i]) 
            return 0;
    return 1;
}

enum Errors copyString(String *dest, const String *src) {
    dest->length = src->length;
    dest->data = (char *)malloc((dest->length + 1) * sizeof(char));
    if (dest->data == NULL)
        return INVALID_MEMORY;
    for (int i = 0; i <= dest->length; i++)
        dest->data[i] = src->data[i];
    return OK;
}

enum Errors cloneString(const String *src, String **newString) {
    *newString = (String *)malloc(sizeof(String));
    if (*newString == NULL)
        return INVALID_MEMORY;
    (*newString)->length = src->length;
    (*newString)->data = (char *)malloc(((*newString)->length + 1) * sizeof(char));
    if ((*newString)->data == NULL){
        free(*newString);
        return INVALID_MEMORY;
    }
    for (int i = 0; i <= (*newString)->length; i++) 
        (*newString)->data[i] = src->data[i];
    return OK;
}

enum Errors concatStrings(String *dest, const String *src) {
    int newLength = dest->length + src->length;
    char *newData = (char *)malloc((newLength + 1) * sizeof(char));
    if (newData == NULL)
        return INVALID_MEMORY;
    for (int i = 0; i < dest->length; i++)
        newData[i] = dest->data[i];
    for (int i = 0; i <= src->length; i++) 
        newData[dest->length + i] = src->data[i];
    free(dest->data);
    dest->data = newData;
    dest->length = newLength;
    return OK;
}

enum Errors printString(const String *str) {
    if (!str)
        return INVALID_INPUT;
    for (int i = 0; i < str->length; i++)
        putchar(str->data[i]);
    putchar('\n');
    return OK;
}