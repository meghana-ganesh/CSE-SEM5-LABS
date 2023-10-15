#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Token 
{
    char name[100];
    int row, col;
    char type[100];
} Token;

int row = 1;
int col = 0;

char *keywords[] = {"const", "char", "int", "return", 
                    "for", "while", "do", "switch", "if", 
                    "else", "unsigned", "case", "break"};

char specialsymbols[] = {'(', ')', '{', '}', '[', ']', ';', ',', ':', '?'};
char arithmeticsymbols[] = {'*', '+', '-', '/'};


int isKeyword(const char *str)
{
    for (int i = 0; i < sizeof(keywords) / sizeof(char *); i++)
    {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int charBelongsTo(char c, const char *arr) 
{
    int len;
    if (arr == specialsymbols)
        len = sizeof(specialsymbols) / sizeof(char);
    else if (arr == arithmeticsymbols)
        len = sizeof(arithmeticsymbols) / sizeof(char);
    for (int i = 0; i < len; i++) 
    {
        if (c == arr[i])
            return 1;
    }
    return 0;
}

void fillToken(Token *tkn, char *name, int row, int col, char *type) 
{
    strcpy(tkn->name, name);
    tkn->row = row;
    tkn->col = col;
    strcpy(tkn->type, type);
}

void printToken(Token *tkn) 
{
    printf("%s %d %d %s\n", tkn->name, tkn->row, tkn->col, tkn->type);
}

Token getNextToken(FILE *fptr1) 
{
    char c;
    int gotToken = 0;
    Token tkn;
    
    while (gotToken == 0 && (c = fgetc(fptr1)) != EOF) 
    {
        if (c == '/')
        {
            int d = fgetc(fptr1);
            col++;
            if (d == '/')
            {
                while ((c = fgetc(fptr1)) != EOF && c != '\n')
                    col++;
                if (c == '\n')
                {
                    row++;
                    col = 0;
                }
            }
        }
        else if(c == '"')
        {
            tkn.row = row;
            tkn.col = col++;
            tkn.name[0] = c;
            int k = 1;
            while ((c = fgetc(fptr1)) != EOF && c != '"')
            {
                tkn.name[k++] = c;
                col++;
            }
            tkn.name[k++] = '"';
            tkn.name[k] = '\0';
            strcpy(tkn.type,"Literal");
            gotToken = 1;
        }
        else if (isalpha(c) || c == '_')
        {
            tkn.row = row;
            tkn.col = col++;
            tkn.name[0] = c;
            int k = 1;
            while ((c = fgetc(fptr1)) != EOF && isalnum(c) || c == '_')
            {
                tkn.name[k++] = c;
                col++;
            }
            tkn.name[k] = '\0';
            if (isKeyword(tkn.name))
                strcpy(tkn.type, "Keyword");
            else
                strcpy(tkn.type, "Identifier");
            gotToken = 1;
            ungetc(c,fptr1);
        }
        else if (isdigit(c))
        {
            tkn.row = row;
            tkn.col = col++;
            tkn.name[0] = c;
            int k = 1;
            while ((c = fgetc(fptr1)) != EOF && isdigit(c))
            {
                tkn.name[k++] = c;
                col++;
            }
            tkn.name[k] = '\0';
            strcpy(tkn.type, "Number");
            gotToken = 1;
            ungetc(c,fptr1);
        }
        else if(c == '\n')
        {
            row++;
            col = 0;
        }
        else if (isspace(c))
            col++;
        else if (charBelongsTo(c, specialsymbols)) 
        {
            char op[2];
            op[0] = c;
            op[1] = '\0';
            fillToken(&tkn, op, row, col, "Special Symbol");
            gotToken = 1;
            col++;
        }
        else if (c == '+')
        {
            int d = fgetc(fptr1);
            if (d != '+')
            {
                char op[2];
                op[0] = c;
                op[1] = '\0';
                fillToken(&tkn, op, row, col, "Arithmetic Symbol");
                gotToken = 1;
                col++;
                ungetc(d,fptr1);
            }
            else
            {
                char op[3];
                op[0] = c;
                op[1] = d;
                op[2] = '\0';
                fillToken(&tkn,op, row, col, "Increment");
                gotToken = 1;
                col += 2;
            }
        }
        else if (c == '-')
        {
            int d = fgetc(fptr1);
            if (d != '-')
            {
                char op[2];
                op[0] = c;
                op[1] = '\0';
                fillToken(&tkn, op, row, col, "Arithmetic Symbol");
                gotToken = 1;
                col++;
                ungetc(d,fptr1);
            }
            else
            {
                char op[3];
                op[0] = c;
                op[1] = d;
                op[2] = '\0';
                fillToken(&tkn, op, row, col, "Decrement");
                gotToken = 1;
                col += 2;
            }
        }
        else if (charBelongsTo(c, arithmeticsymbols)) 
        {
            char op[2];
            op[0] = c;
            op[1] = '\0';
            fillToken(&tkn, op, row, col, "Arithmetic Symbol");
            gotToken = 1;
            col++;
        }
        else if(c == '>' || c == '<' || c == '!' || c == '=')
        {
            int d = fgetc(fptr1);
            if(d == '=')
            {
                char op[3];
                op[0] = c;
                op[1] = d;
                op[2] = '\0';
                fillToken(&tkn,op,row,col,"Relational Operator");
                col += 2;
            }
            else
            {
                ungetc(d,fptr1);
                char op[2];
                op[0] = c;
                op[1] = '\0';
                if(c != '=')
                    fillToken(&tkn,op,row,col,"Relational Operator");
                else
                    fillToken(&tkn,op,row,col,"Assignment Operator");
                col++;
            }
            gotToken = 1;
        }
        else if(c == '&' || c == '|')
        {
            int d = fgetc(fptr1);
            if(d == '&')
            {
                char op[3];
                op[0] = c;
                op[1] = d;
                op[2] = '\0';
                fillToken(&tkn,op,row,col,"Logical Operator");
                col += 2;
            }
            else if(d == '|')
            {
                char op[3];
                op[0] = c;
                op[1] = d;
                op[2] = '\0';
                fillToken(&tkn,op,row,col,"Logical Operator");
                col += 2;
            }
            else
            {
                ungetc(d,fptr1);
                char op[2];
                op[0] = c;
                op[1] = '\0';
                fillToken(&tkn,op,row,col,"Logical Operator");
                col++;
            }
            gotToken = 1;
        }
        
    }
    if (c == EOF) 
    {
            strcpy(tkn.name, ""); // Set an empty name to indicate the end
    }
    return tkn;
}


// int main() 
// {
//     FILE *fptr1 = fopen("input.txt", "r");
//     if (fptr1 == NULL) 
//     {
//         printf("Error opening input file\n");
//         return 1;
//     }

//     while (1) 
//     {
//         Token tkn;
//         tkn = getNextToken(fptr1);
//         if (strcmp(tkn.name, "") == 0) 
//         {
//             printf("End of tokenization\n");
//             break;
//         }
//         printToken(&tkn);
//     }

//     fclose(fptr1);
//     return 0;
// }
