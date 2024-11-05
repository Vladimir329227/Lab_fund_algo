#ifndef MAIN_H_FLAG
#define MAIN_H_FLAG

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#define SIZE_INT 32
#define LINE_SIZE 1024

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    ERROR_OPEN_FILE,
};

typedef struct TreeNode {
    char value;
    struct TreeNode** children;
    int numChildren;
} TreeNode;

int isValidExpression(char* expr);

enum Errors createNode(char value, TreeNode** newNode);

enum Errors addChild(TreeNode* parent, TreeNode* child);

void freeTree(TreeNode* root);

enum Errors buildTree(char* expr, int* index, TreeNode** result);

enum Errors printTree(TreeNode* root, FILE* outputFile, int indent);

#endif