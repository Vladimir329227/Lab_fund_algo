#include <stdio.h>
#include "main.h"

#define NUM 13

int main() {
    // Пример использования overfscanf
    FILE *file = fopen("test.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    int romanValue;
    unsigned int zeckendorfValue;
    int base = 16;
    int hexValue;

    overfscanf(file, "%Ro %Zr %Cv", &romanValue, &zeckendorfValue, &base, &hexValue);

    printf("Roman: %d\n", romanValue);
    printf("Zeckendorf: %u\n", zeckendorfValue);
    printf("Hex: %d\n", hexValue);

    fclose(file);

    // Пример использования oversscanf
    const char *str = "XIX 10110 1a";
    int romanValue2;
    unsigned int zeckendorfValue2;
    int base2 = 16;
    int hexValue2;

    oversscanf(str, "%Ro %Zr %Cv", &romanValue2, &zeckendorfValue2, &base2, &hexValue2);

    printf("Roman: %d\n", romanValue2);
    printf("Zeckendorf: %u\n", zeckendorfValue2);
    printf("Hex: %d\n", hexValue2);

    return 0;
}
