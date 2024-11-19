#include "main.h"

int main(int argc, char *argv[]) {
    if (argc < 2)
        return INVALID_INPUT;

    struct Bus *result = NULL;
    int count = 0;
    for (int i = 1; i < argc; i++)
        if (ParseStopFile(argv[i], &result, &count) != OK)
            return INVALID_INPUT;
    
    printBus(result, count);

    UserMain(result, count);

    freeBus(result, count);
    
    return OK;
}
