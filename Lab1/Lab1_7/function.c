#include "main.h"

enum Errors is_valid_flag(const char *str)
{
    if (str == NULL)
        return INVALID_INPUT;
    if ((str[0] == '-' || str[0] == '/') && str[2] == '\0')
        return OK;
    return INVALID_INPUT;
}

enum Errors convert_str_to_double(const char *str, double * result)
{
    char *endptr;
    *result = strtod(str, &endptr);
    if (*result == HUGE_VAL || *result == -HUGE_VAL)
    {
        return INVALID_INPUT;
    } else if (*endptr != '\0') {
        return INVALID_INPUT;
    }
    
    return OK;
}

char* read_lexeme(FILE* file) {
    if (!file)
        return NULL;
    

    char buffer[256];
    int i = 0;
    int c;

    while ((c = fgetc(file)) != EOF && isspace(c)) {}

    if (c == EOF) {
        return NULL;
    }

    buffer[i++] = c;
    while ((c = fgetc(file)) != EOF && !isspace(c)) {
        buffer[i++] = c;
    }
    buffer[i] = '\0';

    char* lexeme = (char*)malloc(i + 1);
    if (lexeme) {
        strcpy(lexeme, buffer);
    }

    return lexeme;
}

enum Errors merge_files(const char* file1, const char* file2, const char* output_file) {
    if (!file1 || !file2 || !output_file)
        return INVALID_INPUT;

    FILE* f1 = fopen(file1, "r");
    FILE* f2 = fopen(file2, "r");
    FILE* f_out = fopen(output_file, "w");

    if (!f1 || !f2 || !f_out){
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        if (f_out) fclose(f_out);
        return ERROR_OPEN_FILE;
    }

    char* lexeme1 = read_lexeme(f1);
    char* lexeme2 = read_lexeme(f2);

    while (lexeme1 || lexeme2) {
        if (lexeme1) {
            fprintf(f_out, "%s ", lexeme1);
            free(lexeme1);
            lexeme1 = read_lexeme(f1);
        }

        if (lexeme2) {
            fprintf(f_out, "%s ", lexeme2);
            free(lexeme2);
            lexeme2 = read_lexeme(f2);
        }
    }

    fclose(f1);
    fclose(f2);
    fclose(f_out);
    return OK;
}

void convert_to_base4(char *dest, char c) {
    int ascii = (int)c;
    sprintf(dest, "%04o", ascii);
}

void convert_to_base8(char *dest, char c) {
    int ascii = (int)c;
    sprintf(dest, "%03o", ascii);
}

enum Errors process_file(const char *input_path, const char *output_path) {
    if (!input_path || !output_path)
        return INVALID_INPUT;

    FILE *infile = fopen(input_path, "r");
    FILE *outfile = fopen(output_path, "w");

    if (!infile || !outfile){
        if (infile) fclose(infile);
        if (outfile) fclose(outfile);
        return ERROR_OPEN_FILE;        
    }

    char buffer[1024];
    char *lexeme;
    int lexeme_count = 0;
    char base4[5], base8[4];

    while (fgets(buffer, sizeof(buffer), infile)) {
        lexeme = strtok(buffer, " \t\n");
        while (lexeme != NULL) {
            lexeme_count++;

            if (lexeme_count % 10 == 0) {
                for (int i = 0; lexeme[i] != '\0'; i++) {
                    convert_to_base4(base4, tolower(lexeme[i]));
                    fprintf(outfile, "%s", base4);
                }
            } else if (lexeme_count % 2 == 0 && lexeme_count % 10 != 0) {
                for (int i = 0; lexeme[i] != '\0'; i++) {
                    fprintf(outfile, "%c", tolower(lexeme[i]));
                }
            } else if (lexeme_count % 5 == 0 && lexeme_count % 10 != 0) {
                for (int i = 0; lexeme[i] != '\0'; i++) {
                    convert_to_base8(base8, lexeme[i]);
                    fprintf(outfile, "%s", base8);
                }
            } else {
                fprintf(outfile, "%s", lexeme);
            }

            fprintf(outfile, " ");
            lexeme = strtok(NULL, " \t\n");
        }
    }

    fclose(infile);
    fclose(outfile);
    return OK;
}