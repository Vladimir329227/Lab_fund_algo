#include "main.h"

enum Errors createNode(char value, TreeNode** newNode) {
    if (!newNode)
        return INVALID_INPUT;
    *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!(*newNode))
        return INVALID_MEMORY;
    (*newNode)->value = value;
    (*newNode)->children = NULL;
    (*newNode)->numChildren = 0;
    return OK;
}

enum Errors addChild(TreeNode* parent, TreeNode* child) {
    if (!parent || !child)
        return INVALID_INPUT;
    parent->numChildren++;
    parent->children = (TreeNode**)realloc(parent->children, parent->numChildren * sizeof(TreeNode*));
    if (!parent->children)
        return INVALID_MEMORY;
    parent->children[parent->numChildren - 1] = child;
    return OK;
}

void freeTree(TreeNode* root) {
    if (!root)
        return;

    for (int i = 0; i < root->numChildren; i++)
        freeTree(root->children[i]);

    free(root->children);
    free(root);
}

enum Errors buildTree(char* expr, int* index, TreeNode** result) {
    if (expr[*index] == '\0' || expr[*index] == '\n')
        return OK;

    while (expr[*index] == ' ') 
        (*index)++;

    enum Errors err = createNode(expr[*index], result);
    if (err != OK)
        return err;
    
    (*index)++;

    while (expr[*index] == ' ') 
        (*index)++;

    if (expr[*index] == '(') {
        (*index)++;
        while (expr[*index] != ')') {
            TreeNode* child;
            err = buildTree(expr, index, &child);
            if (err != OK){
                freeTree(*result);
                return err;
            }
            err = addChild(*result, child);
            if (err != OK){
                freeTree(*result);
                return err;
            }
            if (expr[*index] == ',' || expr[*index] == ' ') {
                (*index)++;
            }
        }
        (*index)++;
    }

    return OK;
}

enum Errors printTree(TreeNode* root, FILE* outputFile, int indent) {
    if (!root || !outputFile)
        return INVALID_INPUT;
    for (int i = 0; i < indent; i++)
        fprintf(outputFile, " ");
    fprintf(outputFile, "%c\n", root->value);
    for (int i = 0; i < root->numChildren; i++)
        printTree(root->children[i], outputFile, indent + 2);
    return OK;
}