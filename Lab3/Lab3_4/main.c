#include "main.h"

int main() {
    String str1, str2;
    if (createString("Hello", &str1) != OK) {
        printf("Error creating str1\n");
        return INVALID_MEMORY;
    }
    if (createString("World", &str2) != OK) {
        printf("Error creating str2\n");
        deleteString(&str1);
        return INVALID_MEMORY;
    }

    printf("str1: ");
    printString(&str1);
    printf("str2: ");
    printString(&str2);

    String str3;
    if (copyString(&str3, &str1) != OK) {
        printf("Error copying str1 to str3\n");
        deleteString(&str1);
        deleteString(&str2);
        return INVALID_MEMORY;
    }
    printf("str3 (copy of str1): ");
    printString(&str3);

    String *str4 = NULL; 
    if (cloneString(&str2, &str4) != OK) {
        printf("Error cloning str2 to str4\n");
        deleteString(&str1);
        deleteString(&str2);
        deleteString(&str3);
        return INVALID_MEMORY;
    }
    printf("str4 (clone of str2): ");
    printString(str4);

    if (concatStrings(&str1, &str2) != OK) {
        printf("Error concatenating str1 and str2\n");
        return INVALID_MEMORY;
    }
    printf("str1 after concatenation with str2: ");
    printString(&str1);

    printf("Compare str1 and str2: %d\n", compareStrings(&str1, &str2));

    printf("Are str1 and str2 equal? %d\n", areStringsEqual(&str1, &str2));

    deleteString(&str1);
    deleteString(&str2);
    deleteString(&str3);
    deleteString(str4);
    free(str4);

    Address currentAddress;
    createAddress(&currentAddress, "City", "Street", 1, "Building", 1, "123456");

    Post post;
    initPost(&post, &currentAddress);

    interactiveDialog(&post);

    deletePost(&post);
    return OK;
}