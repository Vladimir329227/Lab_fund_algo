#include "main.h"

int main(int argc, char *argv[]) {
    if (argc < 2) 
        return INVALID_INPUT;

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) 
        return ERROR_OPEN_FILE;

    FILE *trace_file = NULL;
    if (argc >= 3 && strcmp(argv[2], "/trace") == 0) {
        if (argc >= 4) {
            trace_file = fopen(argv[3], "w");
            if (!trace_file) {
                return ERROR_OPEN_FILE;
            }
        } else {
            trace_file = stdout;
        }
    }

    bool_vector vars[MAX_VARS] = {0};
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), input_file)) {
        remove_comments(line);
        char *instruction = strtok(line, ";");
        while (instruction) {
            if (execute_instruction(instruction, vars, trace_file) != OK) {
                fclose(input_file);
                if (trace_file && trace_file != stdout) {
                    fclose(trace_file);
                }
                return INVALID_INPUT;
            }
            instruction = strtok(NULL, ";");
        }
    }

    fclose(input_file);
    if (trace_file && trace_file != stdout) {
        fclose(trace_file);
    }

    return 0;
}