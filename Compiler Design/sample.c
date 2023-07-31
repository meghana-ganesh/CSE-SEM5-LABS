#include <stdio.h>

int main() {
    FILE *inputFile, *outputFile;
    char inputFileName[100], outputFileName[100];
    char c;

    // Get the input file name from the user
    printf("Enter the input file name: ");
    scanf("%s", inputFileName);

    // Open the input file in read mode
    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Error opening the input file.\n");
        return 1;
    }

    // Get the output file name from the user
    printf("Enter the output file name: ");
    scanf("%s", outputFileName);

    // Open the output file in write mode
    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Error opening the output file.\n");
        fclose(inputFile);
        return 1;
    }

    // Read characters from the input file and replace spaces and tabs with a single space
    while ((c = fgetc(inputFile)) != EOF) {
        if (c == ' ' || c == '\t') {
            fputc(' ', outputFile); // Replace with a single space
            while ((c = fgetc(inputFile)) == ' ' || c == '\t')
                ; // Skip consecutive spaces and tabs
            ungetc(c, inputFile); // Push back the last non-space/tab character
        } else {
            fputc(c, outputFile); // Copy other characters as it is
        }
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("Spaces and tabs replaced successfully. Output written to %s.\n", outputFileName);

    return 0;
}

//q2
#include <stdio.h>
#include <string.h>

int main() {
    FILE *inputFile, *outputFile;
    char inputFileName[100], outputFileName[100];
    char line[1000];

    // Get the input file name from the user
    printf("Enter the input file name: ");
    scanf("%s", inputFileName);

    // Open the input file in read mode
    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Error opening the input file.\n");
        return 1;
    }

    // Get the output file name from the user
    printf("Enter the output file name: ");
    scanf("%s", outputFileName);

    // Open the output file in write mode
    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Error opening the output file.\n");
        fclose(inputFile);
        return 1;
    }

    // Read lines from the input file and skip lines starting with #
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        if (line[0] == '#') {
            // Skip preprocessor directive lines
            continue;
        }
        // Write non-preprocessor directive lines to the output file
        fputs(line, outputFile);
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("Preprocessor directives discarded successfully. Output written to %s.\n", outputFileName);

    return 0;
}

//q3
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEYWORDS 32
#define MAX_KEYWORD_LEN 20

const char keywords[MAX_KEYWORDS][MAX_KEYWORD_LEN] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
    "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
    "union", "unsigned", "void", "volatile", "while"
};

int main() {
    char inputFileName[100];
    char line[1000];
    int lineNum = 1, colNum;
    int i, j;

    // Get the input file name from the user
    printf("Enter the input C program file name: ");
    scanf("%s", inputFileName);

    // Open the input file in read mode
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Error opening the input file.\n");
        return 1;
    }

    // Read lines from the input file and process each line
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        colNum = 1;
        char *token = strtok(line, " \t\n");

        // Process each word in the line
        while (token != NULL) {
            // Check if the word is a keyword
            for (i = 0; i < MAX_KEYWORDS; i++) {
                if (strcmp(token, keywords[i]) == 0) {
                    // Convert the keyword to uppercase
                    for (j = 0; token[j]; j++) {
                        token[j] = toupper(token[j]);
                    }
                    // Print the keyword along with its line and column numbers
                    printf("Keyword: %s\tLine: %d\tColumn: %d\n", token, lineNum, colNum);
                    break;
                }
            }
            token = strtok(NULL, " \t\n");
            colNum++;
        }

        lineNum++;
    }

    // Close the file
    fclose(inputFile);

    return 0;
}
