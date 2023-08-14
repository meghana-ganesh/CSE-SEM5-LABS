//l2q3
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





//l3 q1 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Token types
typedef enum {
    ARITHMETIC_OP,
    RELATIONAL_OP,
    LOGICAL_OP,
    SPECIAL_SYMBOL,
    KEYWORD,
    NUMERIC_CONSTANT,
    STRING_LITERAL,
    IDENTIFIER
} TokenType;

// Token structure
typedef struct {
    int row;
    int col;
    TokenType type;
    char value[100];
} Token;

// Function to check if a character is a valid identifier character
int isIdentifierChar(char c) {
    return isalnum(c) || c == '_';
}

// Function to identify a token
Token getNextToken(FILE *file, int *row, int *col) {
    Token token;
    token.row = *row;
    token.col = *col;

    char c = fgetc(file);

    while (isspace(c)) {
        if (c == '\n') {
            (*row)++;
            *col = 0;
        } else {
            (*col)++;
        }
        c = fgetc(file);
    }

    if (isalpha(c) || c == '_') {
        // Identifiers or Keywords
        int i = 0;
        while (isIdentifierChar(c)) {
            token.value[i++] = c;
            c = fgetc(file);
        }
        token.value[i] = '\0';

        // Check if the identifier is a keyword
        // Assume "if" and "else" are the only keywords for simplicity
        if (strcmp(token.value, "if") == 0 || strcmp(token.value, "else") == 0) {
            token.type = KEYWORD;
        } else {
            token.type = IDENTIFIER;
        }
    } else if (isdigit(c)) {
        // Numeric Constants
        int i = 0;
        while (isdigit(c)) {
            token.value[i++] = c;
            c = fgetc(file);
        }
        token.value[i] = '\0';
        token.type = NUMERIC_CONSTANT;
    } else if (c == '"') {
        // String Literals
        int i = 0;
        token.value[i++] = c;
        c = fgetc(file);
        while (c != '"') {
            token.value[i++] = c;
            c = fgetc(file);
        }
        token.value[i++] = c;
        token.value[i] = '\0';
        token.type = STRING_LITERAL;
    } else {
        // Special Symbols, Arithmetic, Relational, Logical Operators
        token.value[0] = c;
        token.value[1] = '\0';
        (*col)++;
        if (strchr("+-*/%", c)) {
            token.type = ARITHMETIC_OP;
        } else if (strchr("<>=", c)) {
            token.type = RELATIONAL_OP;
        } else if (strchr("&|!", c)) {
            token.type = LOGICAL_OP;
        } else {
            token.type = SPECIAL_SYMBOL;
        }
    }

    return token;
}

int main() {
    FILE *file = fopen("input.c", "r");
    if (!file) {
        printf("Unable to open file.\n");
        return 1;
    }

    int row = 1, col = 1;
    Token token;
    while (!feof(file)) {
        token = getNextToken(file, &row, &col);
        printf("Row: %d, Col: %d, Type: %d, Value: %s\n", token.row, token.col, token.type, token.value);
        col += strlen(token.value);
    }

    fclose(file);
    return 0;
}

