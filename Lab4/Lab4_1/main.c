#include "main.h"

int main(int argc, char* argv[]) {
    if (argc != 2)
        return INVALID_INPUT;

    process_file(argv[1]);

    return OK;
}
