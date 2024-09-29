#include <stdio.h>
#include "main.h"

int main() { 
    int base;
    printf("Enter the base of the number system (from 2 to 36): ");
    scanf("%d", &base);
    getchar();

    if (base < 2 || base > 36) {
        return INVALID_INPUT;
    }

    long long int maxNum = 0;
    char input[100];
    long long int num;
    char *token;

    while (1) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "Stop") == 0) {
            break;
        }

        token = strtok(input, " \t\n");
        while (token != NULL) {
            if (convertToDecimal(token, base, &num) != OK){
                printf("INVALID_INPUT");
                return INVALID_INPUT;
            }
            if (llabs(num) > llabs(maxNum)) {
                maxNum = num;
            }
            token = strtok(NULL, " \t\n");
        }
    }

    printf("Maximum number: %lld\n", maxNum);

    char result[100];
    int bases[] = {9, 18, 27, 36};

    for (int i = 0; i < 4; i++) {
        convertToBase(maxNum, bases[i], result);
        printf("String representation in radix number system %d: %s\n", bases[i], result);
    }

    return OK;
}
