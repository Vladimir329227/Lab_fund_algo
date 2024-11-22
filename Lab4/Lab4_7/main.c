#include "main.h"

int main(int argc, char *argv[]) {
    if (argc != 2) 
        return INVALID_INPUT;

    MemoryArray array = {NULL, 0, 0};
    execute_instructions(&array, argv[1]);
    free_memory_array(&array);

    return 0;
}