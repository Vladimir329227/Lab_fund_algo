#include "main.h"

void input_liver_data(struct Liver *data) {
    printf("Enter name: ");
    scanf("%s", data->name);

    printf("Enter surname: ");
    scanf("%s", data->surname);

    printf("Enter patronymic (or enter 0 to skip): ");
    scanf("%s", data->patronymic);
    if (data->patronymic[0] == '0')
        data->patronymic[0] = '\0';

    printf("Enter year: ");
    scanf("%hd", &data->year);

    printf("Enter month: ");
    scanf("%hd", &data->month);

    printf("Enter day: ");
    scanf("%hd", &data->day);

    printf("Enter sex (M/F): ");
    scanf(" %c", &data->sex);

    printf("Enter salary: ");
    scanf("%f", &data->salary);
}

int main(int argc, char* argv[]) {
    if (argc != 3)
        return INVALID_INPUT;

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile)
        return ERROR_OPEN_FILE;

    if (is_file_path(argv[1], argv[2]) != OK) {
        fclose(inputFile);
        return INVALID_INPUT;
    }

    size_t size = 0;
    struct StringlyLinkedList *liver = NULL;
    enum Errors err = read_file(&liver, inputFile, &size);
    if (err != OK) {
        free_list(liver);
        fclose(inputFile);
        printf("Error reading file\n");
        return err;
    }

    fclose(inputFile);

    printf("File read successfully\n");

    char command[50];
    struct Modification* history = NULL;
    size_t history_size = 0;
    int param;
    char value[LEN_NAME];
    while (1) {
        printf("Enter command number:\n");
        printf("1. Search\n");
        printf("2. Update\n");
        printf("3. Remove\n");
        printf("4. Add\n");
        printf("5. Undo\n");
        printf("6. Save\n");
        printf("7. Print List\n");
        printf("8. Exit\n");
        scanf("%s", command);

        if (strcmp(command, "1") == 0) {
            printf("Enter search parameter (1 - name, 2 - surname, 3 - patronymic, 4 - year, 5 - month, 6 - day, 7 - sex, 8 - salary): ");
            scanf("%d", &param);
            printf("Enter value to search: ");
            scanf("%s", value);
            err = search_liver(liver, param, value);
            if (err != OK)
                printf("Search failed\n");
        } else if (strcmp(command, "2") == 0) {
            struct Liver old_data, new_data;
            printf("Enter data to found (name surname year.month.day): ");
            scanf("%s %s %hd.%hd.%hd", old_data.name, old_data.surname, &old_data.year, &old_data.month, &old_data.day);
            input_liver_data(&new_data);
            err = update_liver_mod(&liver, old_data, new_data, &history, &history_size);
            if (err != OK) 
                printf("Update failed\n");
        } else if (strcmp(command, "3") == 0) {
            struct Liver data;
            printf("Enter data to remove (name surname year.month.day): ");
            scanf("%s %s %hd.%hd.%hd", data.name, data.surname, &data.year, &data.month, &data.day);
            err = remove_liver_mod(&liver, data, &history, &history_size, &size);
            if (err != OK)
                printf("Remove failed\n");
        } else if (strcmp(command, "4") == 0) {
            struct Liver data;
            input_liver_data(&data);
            err = add_liver_mod(&liver, data, &history, &history_size, &size);
            if (err != OK)
                printf("Add failed\n");
        } else if (strcmp(command, "5") == 0) {
            err = undo_modifications(&liver, &history, &history_size, &size);
            if (err != OK) 
                printf("Undo failed\n");
        } else if (strcmp(command, "6") == 0) {
            char output_path[256];
            printf("Enter output file path: ");
            scanf("%s", output_path);
            FILE* outputFile = fopen(output_path, "w");
            if (!outputFile) {
                printf("Failed to open output file\n");
                continue;
            }
            err = wreite_file(liver, outputFile, size);
            fclose(outputFile);
            if (err != OK)
                printf("Save failed\n");
        } else if (strcmp(command, "7") == 0) {
            print_list(liver);
        } else if (strcmp(command, "8") == 0) {
            break;
        } else {
            printf("Unknown command\n");
        }

        if (err != OK)
            break;
    }

    FILE* outputFile = fopen(argv[2], "w");
    if (!outputFile) 
        return ERROR_OPEN_FILE;

    err = wreite_file(liver, outputFile, size);
    if (err != OK) {
        fclose(outputFile);
        return err;
    }
    fclose(outputFile);
    free_list(liver);
    free(history);
    return err;
}
