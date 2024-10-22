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

enum Errors read_lexeme(FILE* file, char* lexeme) {
    if (!file)
        return ERROR_OPEN_FILE;
    

    char buffer[256];
    int i = 0;
    int c;

    while ((c = fgetc(file)) != EOF && isspace(c)) {}

    if (c == EOF) {
        return INVALID_INPUT;
    }

    buffer[i++] = c;
    while ((c = fgetc(file)) != EOF && !isspace(c)) {
        buffer[i++] = c;
    }
    buffer[i] = '\0';
    lexeme = (char*)malloc(i + 1);
    if (lexeme == NULL)
        return INVALID_MEMORY;
    if (lexeme) {
        strcpy(lexeme, buffer);
    }

    return OK;
}

enum Errors merge_files(const char* file1, const char* file2, const char* output_file) {
    if (!file1 || !file2 || !output_file)
        return INVALID_INPUT;
    
    char real_path_f1[PATH_MAX];
    char real_path_f2[PATH_MAX];
    char real_path_out[PATH_MAX];

    if (_fullpath(real_path_f1,file1,PATH_MAX) == NULL || _fullpath(real_path_f2,file2,PATH_MAX) == NULL || _fullpath(real_path_out,output_file,PATH_MAX) == NULL)
        return ERROR_OPEN_FILE;
    
    if (strcmp(real_path_f2, real_path_f1) == 0 || strcmp(real_path_f2, real_path_out) == 0 || strcmp(real_path_f1, real_path_out) == 0)
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

    char* lexeme1 = NULL, *lexeme2 = NULL;
    switch (read_lexeme(f1, lexeme1))
    {
    case INVALID_INPUT:
        return INVALID_INPUT;
    case INVALID_MEMORY:
        return INVALID_MEMORY;
    case ERROR_OPEN_FILE:
        return ERROR_OPEN_FILE;
    default:
        break;
    } 
    switch (read_lexeme(f2, lexeme2))
    {
    case INVALID_INPUT:
        return INVALID_INPUT;
    case INVALID_MEMORY:
        return INVALID_MEMORY;
    case ERROR_OPEN_FILE:
        return ERROR_OPEN_FILE;
    default:
        break;
    } 

    while (lexeme1 || lexeme2) {
        if (lexeme1) {
            fprintf(f_out, "%s ", lexeme1);
            free(lexeme1);
            lexeme1 = NULL;
            switch (read_lexeme(f1, lexeme1))
            {
            case INVALID_INPUT:
                return INVALID_INPUT;
            case INVALID_MEMORY:
                return INVALID_MEMORY;
            case ERROR_OPEN_FILE:
                return ERROR_OPEN_FILE;
            default:
                break;
            } 
        }

        if (lexeme2) {
            fprintf(f_out, "%s ", lexeme2);
            free(lexeme2);
            lexeme2 = NULL;
            switch (read_lexeme(f2, lexeme2))
            {
            case INVALID_INPUT:
                return INVALID_INPUT;
            case INVALID_MEMORY:
                return INVALID_MEMORY;
            case ERROR_OPEN_FILE:
                return ERROR_OPEN_FILE;
            default:
                break;
            } 
        }
    }

    fclose(f1);
    fclose(f2);
    fclose(f_out);
    return OK;
}

void convert_to_base4(char *dest, char c, int size) {
    int ascii = (int)c;
    int cur_razm = 1;
    while (cur_razm <= size)
    {
        dest[size - cur_razm] = '0' + ascii%4;
        ascii/=4;
        cur_razm++;
    }    
}

void convert_to_base8(char *dest, char c, int size) {
    int ascii = (int)c;
    int cur_razm = 1;
    while (cur_razm <= size)
    {
        dest[size - cur_razm] = '0' + ascii%8;
        ascii/=8;
        cur_razm++;
    } 
}

enum Errors process_file(const char *input_path, const char *output_path) {
    if (!input_path || !output_path)
        return INVALID_INPUT;
    
    char real_input_path[PATH_MAX];
    char real_output_path[PATH_MAX];


    if (_fullpath(real_input_path,input_path,PATH_MAX) == NULL || _fullpath(real_output_path,output_path,PATH_MAX) == NULL) 
        return ERROR_OPEN_FILE;

    if (strcmp(real_input_path, real_output_path) == 0)
        return INVALID_INPUT;


    FILE *infile = fopen(input_path, "r");
    FILE *outfile = fopen(output_path, "w");

    if (!infile || !outfile){
        if (infile) fclose(infile);
        if (outfile) fclose(outfile);
        return ERROR_OPEN_FILE;        
    }

    char buffer[1024];
    int buffer_index = 0;
    int lexeme_count = 0;
    int c;

    char base8[4], base4[6];


    while ((c = fgetc(infile)) != EOF) {
        if (isspace(c)) {
            if (buffer_index > 0) {
                buffer[buffer_index] = '\0';
                lexeme_count++;

                if (lexeme_count % 10 == 0) {
                    for (int i = 0; buffer[i] != '\0'; i++) {
                        convert_to_base4(base4, tolower(buffer[i]), 6);
                        fprintf(outfile, "%s", base4);
                    }
                } else if (lexeme_count % 2 == 0 && lexeme_count % 10 != 0) {
                    for (int i = 0; buffer[i] != '\0'; i++) {
                        fprintf(outfile, "%c", tolower(buffer[i]));
                    }
                } else if (lexeme_count % 5 == 0 && lexeme_count % 10 != 0) {
                    for (int i = 0; buffer[i] != '\0'; i++) {
                        convert_to_base8(base8, buffer[i], 4);
                        fprintf(outfile, "%s", base8);
                    }
                } else {
                    fprintf(outfile, "%s", buffer);
                }

                fprintf(outfile, " ");
                buffer_index = 0;
            }
        } else {
            buffer[buffer_index++] = c;
        }
    }

    if (buffer_index > 0) {
        buffer[buffer_index] = '\0';
        lexeme_count++;

        if (lexeme_count % 10 == 0) {
            for (int i = 0; buffer[i] != '\0'; i++) {
                convert_to_base4(base4, tolower(buffer[i]), 6);
                fprintf(outfile, "%s", base4);
            }
        } else if (lexeme_count % 2 == 0 && lexeme_count % 10 != 0) {
            for (int i = 0; buffer[i] != '\0'; i++) {
                fprintf(outfile, "%c", tolower(buffer[i]));
            }
        } else if (lexeme_count % 5 == 0 && lexeme_count % 10 != 0) {
            for (int i = 0; buffer[i] != '\0'; i++) {
                convert_to_base8(base8, buffer[i], 4);
                fprintf(outfile, "%s", base8);
            }
        } else {
            fprintf(outfile, "%s", buffer);
        }

        fprintf(outfile, " ");
    }

    fclose(infile);
    fclose(outfile);
    return OK;
}