#include "main.h"


int main(int argc, char* argv[]) {
    if (argc != 3)
        return INVALID_INPUT;

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile)
        return ERROR_OPEN_FILE;
    
    FILE* outputFile = fopen(argv[2], "w");
    if (!outputFile) {
        fclose(inputFile);
        return ERROR_OPEN_FILE;
    }

    char line[1024];
    enum Errors error = OK;
    while (fgets(line, sizeof(line), inputFile)) {

        int index = 0;
        TreeNode* root;
        error = buildTree(line, &index, &root);
        if (error != OK){
            freeTree(root);
            return error;
        }
        printTree(root, outputFile, 0);
        fprintf(outputFile, "---------------------------------------------------\n");
        freeTree(root);
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
