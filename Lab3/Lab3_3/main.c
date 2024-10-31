#include "main.h"


int main(int argc, char* argv[]) {
    if (argc != 4)
        return INVALID_INPUT;

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile)
        return ERROR_OPEN_FILE;
    
    if (is_valid_flag(argv[2]) != OK){
        fclose(inputFile);
        return INVALID_INPUT;
    }

    FILE* outputFile = fopen(argv[3], "w");
    if (!outputFile) {
        fclose(inputFile);
        return ERROR_OPEN_FILE;
    }

    size_t size = 0;
    struct Employee *employees = NULL;
    enum Errors err = read_file(&employees, inputFile, &size);
    if (err != OK) {
        fclose(inputFile);
        fclose(outputFile);
        return err;
    }

    if (argv[2][1] == 'a')
        qsort(employees, size, sizeof(struct Employee), compare);
    else if (argv[2][1] == 'd')
        qsort(employees, size, sizeof(struct Employee), reverse_compare);
    else{
        fclose(inputFile);
        fclose(outputFile);
        return INVALID_INPUT;
    }

    err = wreite_file(employees, outputFile, size);
    if (err != OK) {
        fclose(inputFile);
        fclose(outputFile);
        return err;
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
