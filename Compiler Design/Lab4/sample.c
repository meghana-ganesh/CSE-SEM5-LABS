#include <stdio.h>
#include <string.h>

typedef struct Token {
    int row_no;
    int col_no;
    char type[256];
    char lexeme[256];
} Token;

typedef struct SymbolTableEntry {
    char name[256];
    char type[256];
} SymbolTableEntry;

SymbolTableEntry globalSymbolTable[100];
SymbolTableEntry localSymbolTable[100];
int globalSymbolTableSize = 0;
int localSymbolTableSize = 0;

void insertSymbolEntry(SymbolTableEntry symbolTable[], int *size, char *name, char *type) {
    SymbolTableEntry entry;
    strcpy(entry.name, name);
    strcpy(entry.type, type);
    symbolTable[*size] = entry;
    (*size)++;
}

int searchSymbolEntry(SymbolTableEntry symbolTable[], int size, char *name) {
    for (int i = 0; i < size; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return i; // Entry found
        }
    }
    return -1; // Entry not found
}

void processToken(Token token) {
    if (strcmp(token.type, "Identifier") == 0) {
        int localIndex = searchSymbolEntry(localSymbolTable, localSymbolTableSize, token.lexeme);

        if (localIndex != -1) {
            printf("Local symbol found: %s\n", localSymbolTable[localIndex].name);
        } else {
            int globalIndex = searchSymbolEntry(globalSymbolTable, globalSymbolTableSize, token.lexeme);

            if (globalIndex != -1) {
                printf("Global symbol found: %s\n", globalSymbolTable[globalIndex].name);
            } else {
                printf("Symbol not found: %s\n", token.lexeme);
            }
        }
    }
}

int main() {
    // Simulated token stream
    Token tokens[] = {
        {1, 1, "Identifier", "variable1"},
        {1, 10, "Identifier", "variable2"},
        // ... Other tokens
    };

    for (int i = 0; i < sizeof(tokens) / sizeof(tokens[0]); i++) {
        Token token = tokens[i];
        processToken(token);
    }

    return 0;
}
