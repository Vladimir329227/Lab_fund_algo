#include "main.h"

int main(int argc, char *argv[]) {
    if (argc < 3)
        return INVALID_INPUT;

    const char *inputFile = argv[1];
    const char *outputFile = argv[2];
    char *trassFile = NULL;

    if (argc > 3) {
        trassFile = argv[3];
    }

    enum Errors err = OK;
    int count;
    Student *students;
    err = readStudentsFromFile(inputFile, &count, &students);
    if (err != OK) {
        return err;
    }

    int choice;
    do {
        printf("Menu:\n");
        printf("1. Find student by ID\n");
        printf("2. Find students by surname\n");
        printf("3. Find students by name\n");
        printf("4. Find students by group\n");
        printf("5. Sort students by ID\n");
        printf("6. Sort students by surname\n");
        printf("7. Sort students by name\n");
        printf("8. Sort students by group\n");
        printf("9. Write student data to file\n");
        printf("10. Write high average students to file\n");
        printf("11. Print all students\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                unsigned int id;
                printf("Enter ID: ");
                scanf("%u", &id);
                Student *student = findStudentById(students, count, id);
                if (student) {
                    printf("Student found: ID=%u, Name=%s %s, Group=%s\n",
                           student->id, student->name, student->surname, student->group);
                    if (trassFile) {
                        writeStudentDataToFile(trassFile, student);
                    }
                } else {
                    printf("Student not found\n");
                }
                break;
            }
            case 2: {
                char surname[50];
                printf("Enter surname: ");
                scanf("%49s", surname);
                int foundCount;
                Student *foundStudents;
                err = findStudentsBySurname(students, count, surname, &foundCount, &foundStudents);
                if (err != OK) {
                    break;
                }
                if (foundCount > 0) {
                    if (trassFile) {
                        writeStudentDataToFile(trassFile, foundStudents);
                    }
                    printf("Students found:\n");
                    for (int i = 0; i < foundCount; i++) {
                        printf("ID=%u, Name=%s %s, Group=%s\n",
                               foundStudents[i].id, foundStudents[i].name, foundStudents[i].surname, foundStudents[i].group);
                               
                    }
                } else {
                    printf("No students found\n");
                }
                free(foundStudents);
                break;
            }
            case 3: {
                char name[50];
                printf("Enter name: ");
                scanf("%49s", name);
                int foundCount;
                Student *foundStudents;
                err = findStudentsByName(students, count, name, &foundCount, &foundStudents);
                if (err != OK) {
                    break;
                }
                if (foundCount > 0) {
                    if (trassFile) {
                        writeStudentDataToFile(trassFile, foundStudents);
                    }
                    printf("Students found:\n");
                    for (int i = 0; i < foundCount; i++) {
                        printf("ID=%u, Name=%s %s, Group=%s\n",
                               foundStudents[i].id, foundStudents[i].name, foundStudents[i].surname, foundStudents[i].group);
                    }
                } else {
                    printf("No students found\n");
                }
                free(foundStudents);
                break;
            }
            case 4: {
                char group[50];
                printf("Enter group: ");
                scanf("%49s", group);
                int foundCount;
                Student *foundStudents;
                err = findStudentsByGroup(students, count, group, &foundCount, &foundStudents);
                if (err != OK) {
                    break;
                }
                if (foundCount > 0) {
                    if (trassFile) {
                        writeStudentDataToFile(trassFile, foundStudents);
                    }
                    printf("Students found:\n");
                    for (int i = 0; i < foundCount; i++) {
                        printf("ID=%u, Name=%s %s, Group=%s\n",
                               foundStudents[i].id, foundStudents[i].name, foundStudents[i].surname, foundStudents[i].group);
                    }
                } else {
                    printf("No students found\n");
                }
                free(foundStudents);
                break;
            }
            case 5:
                qsort(students, count, sizeof(Student), compareById);
                printf("Students sorted by ID\n");
                break;
            case 6:
                qsort(students, count, sizeof(Student), compareBySurname);
                printf("Students sorted by surname\n");
                break;
            case 7:
                qsort(students, count, sizeof(Student), compareByName);
                printf("Students sorted by name\n");
                break;
            case 8:
                qsort(students, count, sizeof(Student), compareByGroup);
                printf("Students sorted by group\n");
                break;
            case 9: {
                unsigned int id;
                printf("Enter ID: ");
                scanf("%u", &id);
                Student *student = findStudentById(students, count, id);
                if (student) {
                    if (trassFile) {
                        writeStudentDataToFile(trassFile, student);
                    }
                    writeStudentDataToFile(outputFile, student);
                    printf("Student data written to file\n");
                } else {
                    printf("Student not found\n");
                }
                break;
            }
            case 10:
                if (trassFile) {
                    err = writeHighAverageStudentsToFile(trassFile, students, count);
                    if (err != OK)
                        break;
                }
                err = writeHighAverageStudentsToFile(outputFile, students, count);
                if (err == OK)
                    break;
                printf("High average students written to file\n");
                break;
            case 11:
                PrintStudents(students, count);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (choice != 0);

    freeStudents(students, count);
    return err;
}
