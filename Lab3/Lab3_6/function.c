#include "main.h"

int isValidName(const char *name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i])) {
            return 0;
        }
    }
    return 1;
}

enum Errors readStudentsFromFile(const char *filename, int *count, Student** students) {
    if (!filename || !count || !students)
        return INVALID_INPUT;
    FILE *file = fopen(filename, "r");
    if (!file)
        return ERROR_OPEN_FILE;

    *students = NULL;
    int capacity = 0;
    *count = 0;

    while (!feof(file)) {
        if (*count >= capacity) {
            capacity = capacity == 0 ? 1 : capacity * 2;
            *students = realloc(*students, capacity * sizeof(Student));
            if (!*students) {
                fclose(file);
                return INVALID_MEMORY;
            }
        }

        if (fscanf(file, "%u %49s %49s %49s", &((*students)[*count]).id, (*students)[*count].name, (*students)[*count].surname, (*students)[*count].group) != 4) {
            break;
        }

        if (!isValidName((*students)[*count].name) || !isValidName((*students)[*count].surname)) {
            break;
        }

        (*students)[*count].grades = malloc(5 * sizeof(unsigned char));
        if (!(*students)[*count].grades) {
            fclose(file);
            free(*students);
            return INVALID_MEMORY;
        }
        for (int i = 0; i < 5; i++) {
            if (fscanf(file, "%hhu", &(*students)[*count].grades[i]) != 1) {
                break;
            }
        }

        (*count)++;
    }

    fclose(file);
    if (*count == 0) {
        free(*students);
        *students = NULL;
        return INVALID_INPUT;
    }
    return OK;
}

void freeStudents(Student *students, int count) {
    for (int i = 0; i < count; i++) {
        free(students[i].grades);
    }
    free(students);
}

Student* findStudentById(Student *students, int count, unsigned int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            return &students[i];
        }
    }
    return NULL;
}

enum Errors findStudentsBySurname(Student *students, int count, const char *surname, int *foundCount, Student **result) {
    if (!surname || !foundCount || !result)
        return INVALID_INPUT;
    *result = malloc(count * sizeof(Student));
    if (!*result) {
        return INVALID_MEMORY;
    }
    *foundCount = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].surname, surname) == 0) {
            (*result)[*foundCount] = students[i];
            (*foundCount)++;
        }
    }

    return OK;
}

enum Errors findStudentsByName(Student *students, int count, const char *name, int *foundCount, Student **result) {
    if (!name || !foundCount || !result)
        return INVALID_INPUT;
    *result = malloc(count * sizeof(Student));
    if (!*result) {
        return INVALID_MEMORY;
    }
    *foundCount = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            (*result)[*foundCount] = students[i];
            (*foundCount)++;
        }
    }

    return OK;
}

enum Errors findStudentsByGroup(Student *students, int count, const char *group, int *foundCount, Student **result) {
    if (!group || !foundCount || !result)
        return INVALID_INPUT;
    *result = malloc(count * sizeof(Student));
    if (!*result) {
        return INVALID_MEMORY;
    }
    *foundCount = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].group, group) == 0) {
            (*result)[*foundCount] = students[i];
            (*foundCount)++;
        }
    }

    return OK;
}

float calculateAverageGrade(unsigned char *grades, int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += grades[i];
    }
    return (float)sum / count;
}

enum Errors writeStudentDataToFile(const char *filename, Student *student) {
    if (!filename || !student)
        return INVALID_INPUT;
    FILE *file = fopen(filename, "a");
    if (!file) {
        return ERROR_OPEN_FILE;
    }

    float averageGrade = calculateAverageGrade(student->grades, 5);
    fprintf(file, "ID: %u, Name: %s %s, Group: %s, Average Grade: %.2f\n",
            student->id, student->name, student->surname, student->group, averageGrade);

    fclose(file);
    return OK;
}

enum Errors writeHighAverageStudentsToFile(const char *filename, Student *students, int count) {
    if (!filename || !students || count < 1)
        return INVALID_INPUT;
    FILE *file = fopen(filename, "a");
    if (!file) {
        return ERROR_OPEN_FILE;
    }

    float overallAverage = 0;
    for (int i = 0; i < count; i++) {
        overallAverage += calculateAverageGrade(students[i].grades, 5);
    }
    overallAverage /= count;

    float averageGrade = 0;
    fprintf(file, "Students with average grade higher than %.2f:\n", overallAverage);
    for (int i = 0; i < count; i++) {
        averageGrade = calculateAverageGrade(students[i].grades, 5);
        if (averageGrade > overallAverage) {
            fprintf(file, "Name: %s %s\n", students[i].name, students[i].surname);
        }
    }

    fclose(file);
    return OK;
}

int compareById(const void *a, const void *b) {
    return ((Student *)a)->id - ((Student *)b)->id;
}

int compareBySurname(const void *a, const void *b) {
    return strcmp(((Student *)a)->surname, ((Student *)b)->surname);
}

int compareByName(const void *a, const void *b) {
    return strcmp(((Student *)a)->name, ((Student *)b)->name);
}

int compareByGroup(const void *a, const void *b) {
    return strcmp(((Student *)a)->group, ((Student *)b)->group);
}

void PrintStudents(Student *students, int count) {
    for (int i = 0; i < count; i++) {
        printf("ID: %u, Name: %s %s, Group: %s\n",
               students[i].id, students[i].name, students[i].surname, students[i].group);
    }
}