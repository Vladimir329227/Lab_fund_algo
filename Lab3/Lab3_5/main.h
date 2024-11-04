#ifndef MAIN_H_FLAG
#define MAIN_H_FLAG
#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#define LEN_NAME 70

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    ERROR_OPEN_FILE,
};

typedef struct {
    unsigned int id;
    char name[50], surname[50], group[50];
    unsigned char *grades;
} Student;

int isValidName(const char *name);

enum Errors readStudentsFromFile(const char *filename, int *count, Student** students);
enum Errors writeHighAverageStudentsToFile(const char *filename, Student *students, int count);
enum Errors writeStudentDataToFile(const char *filename, Student *student);

float calculateAverageGrade(unsigned char *grades, int count);

void freeStudents(Student *students, int count);

void PrintStudents(Student *students, int count);

enum Errors findStudentsByGroup(Student *students, int count, const char *group, int *foundCount, Student **result);
enum Errors findStudentsByName(Student *students, int count, const char *name, int *foundCount, Student **result);
enum Errors findStudentsBySurname(Student *students, int count, const char *surname, int *foundCount, Student **result);
Student* findStudentById(Student *students, int count, unsigned int id);

int compareById(const void *a, const void *b);
int compareBySurname(const void *a, const void *b);
int compareByName(const void *a, const void *b);
int compareByGroup(const void *a, const void *b);

#endif