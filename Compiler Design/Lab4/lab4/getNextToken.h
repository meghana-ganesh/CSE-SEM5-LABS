#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
typedef struct Token
{
    int row_no;
    int col_no;
    char type[256];
    char token[256];
}Token;

int ind = 0;

char keywords[16][10]={"if","else","int","float","char",
"break","case","continue","default","double","for","while","return","sizeof","struct","void"};

int ArithOp(char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/')
    {
        return 1;
    }
    return 0;
}

int LogicalOp(char c)
{
    if(c == '!' || c == '&' || c == '|')
    {
        return 1;
    }
    return 0;
}

int RelOp(char c)
{
    if(c == '>' || c == '<' || c == '=' || c == '!')
    {
        return 1;
    }
    return 0;
}

int isStringLiteral(char line[],int i,int *start_ind)
{
    int end_ind = i;
    if(line[end_ind] == '"')
    {
        (*start_ind) = end_ind;
        end_ind++;
        while(line[end_ind] != '"')
        {
            end_ind++;
        }
    }
    return end_ind;
}

void createToken(Token token[256],int row_no,int col_no,char *tok,char *str)
{
    strcpy(token[ind].type,tok);
    strcpy(token[ind].type,str);
    token[ind].row_no = row_no;
    token[ind].col_no = col_no;
    ind++;
}
void getSpecialSymbol(char line[],int row_no,Token token[256])
{
    for(int i=0;i<strlen(line);i++)
    {
        int x = 0;
        i = isStringLiteral(line,i,&x);
        char symbol[2];
        switch(line[i])
        {
            case '$':
                symbol[0] = line[i];
                symbol[1] = '\0';
                createToken(token,row_no,i,symbol,"SYMBOL");
                i++;
                break;
            case ',':
                symbol[0] = line[i];
                symbol[1] = '\0';
                createToken(token,row_no,i,symbol,"SYMBOL");
                i++;
                break;
            case ';':
                symbol[0] = line[i];
                symbol[1] = '\0';
                createToken(token,row_no,i,symbol,"SYMBOL");
                i++;
                break;
            case '(':
                symbol[0] = line[i];
                symbol[1] = '\0';
                createToken(token,row_no,i,symbol,"SYMBOL");
                break;
            case ')':
                symbol[0] = line[i];
                symbol[1] = '\0';
                createToken(token,row_no,i,symbol,"SYMBOL");
                break;
            case '{':
                symbol[0] = line[i];
                symbol[1] = '\0';
                createToken(token,row_no,i,symbol,"SYMBOL");
                break;
            case '}':
                symbol[0] = line[i];
                symbol[1] = '\0';
                createToken(token,row_no,i,symbol,"SYMBOL");
                break;
            default:
                break;
        }
    }
}

void getArithOp(char line[],int row_no,Token token[256])
{
    for(int i=0;i<strlen(line);i++)
    {
        int x = 0;
        i = isStringLiteral(line,i,&x);
        if(!ArithOp(line[i]))
            continue;
        if(ArithOp(line[i]) && !ArithOp(line[i+1]) && !ArithOp(line[i-1]) && (i+1)<strlen(line))
        {
            if(line[i] == '+')
            {
                char op[2];
                op[0] = line[i];
                op[1] = '\0';
                createToken(token,row_no,i,op,"ADD");
            }
            else if(line[i] == '-')
            {
                char op[2];
                op[0] = line[i];
                op[1] = '\0';
                createToken(token,row_no,i,op,"SUB");
            }
            else if(line[i] == '*')
            {
                char op[2];
                op[0] = line[i];
                op[1] = '\0';
                createToken(token,row_no,i,op,"MUL");
            }
            else if(line[i] == '/')
            {
                char op[2];
                op[0] = line[i];
                op[1] = '\0';
                createToken(token,row_no,i,op,"DIV");
            }
        }
    }
}

void getLogicalOp(char line[],int row_no,Token token[256])
{
    for(int i=0;i<strlen(line);i++)
    {
        int x = 0;
        i = isStringLiteral(line,i,&x);
        if(!LogicalOp(line[i]))
            continue;
        if((i+1) < strlen(line))
        {
            if(line[i] == '&' && line[i+1] == '&')
            {
                char op[3];
                char op[0] = line[i];
                char op[1] = line[i+1];
                char op[2] = '\0';
                createToken(token,row_no,i,op,"LogicalAND");
                i++;
            }
            else if(line[i] == '|' && line[i] == '|')
            {
                char op[3];
                char op[0] = line[i];
                char op[1] = line[i+1];
                char op[2] = '\0';
                createToken(token,row_no,i,op,"LogicalOR");
                i++;
            }
            else if(line[i] == '!' && !LogicalOp(line[i+1]) && line[i+1] != '=')
            {
                char op[3];
                char op[0] = line[i];
                char op[1] = line[i+1];
                char op[2] = '\0';
                createToken(token,row_no,i,op,"LogicalNOT");
                i++;
            }
        }
    }
}

void getRelOp(char line[],int row_no,Token token[256])
{
    for(int i=0;i<strlen(line);i++)
    {
        int x = 0;
        i = isStringLiteral(line,i,&x);
        if(!RelOp(line[i]))
            continue;
        if((i+1) < strlen(line))
        {
            if(line[i] == '!' && line[i+1] == '=')
            {
                char op[3];
                char op[0] = line[i];
                char op[1] = line[i+1];
                char op[2] = '\0';
                createToken(token,row_no,i,op,"Relop:NE");
                i++;
            }
            else if(line[i] == '=' && line[i+1] == '=')
            {
                char op[3];
                char op[0] = line[i];
                char op[1] = line[i+1];
                char op[2] = '\0';
                createToken(token,row_no,i,op,"Relop:EQ");
                i++;
            }
            else if(line[i] == '<' && line[i+1] == '=')
            {
                char op[3];
                char op[0] = line[i];
                char op[1] = line[i+1];
                char op[2] = '\0';
                createToken(token,row_no,i,op,"Relop:LE");
                i++;
            }
            else if(line[i] == '>' && line[i+1] == '=')
            {
                char op[3];
                char op[0] = line[i];
                char op[1] = line[i+1];
                char op[2] = '\0';
                createToken(token,row_no,i,op,"Relop:GE");
                i++;
            }
            else if(line[i] == '<' && !RelOp(line[i+1]))
            {
                char op[3];
                char op[0] = line[i];
                char op[1] = line[i+1];
                char op[2] = '\0';
                createToken(token,row_no,i,op,"Relop:LT");
                i++;
            }
            else if(line[i] == '>' && !RelOp(line[i+1]))
            {
                char op[3];
                char op[0] = line[i];
                char op[1] = line[i+1];
                char op[2] = '\0';
                createToken(token,row_no,i,op,"Relop:GT");
                i++;
            }
            else if(line[i] == '=' && !RelOp(line[i+1]))
            {
                char op[2];
                char op[0] = line[i];
                char op[1] = '\0';
                createToken(token,row_no,i,"AssignmentOP:=");
                i++;
            }
        }
    }
}

void getStringLiteral(char line[],int row_no,Token token[256])
{
    for(int i=0;i<strlen(line);i++)
    {
        int start_ind = 0;
        int end_ind = isStringLiteral(line,i,&start_ind);
        if(i == end_ind)
            continue;
        char literal[256];
        int k = 0;
        for(int j=start_ind;j<=end_ind;j++)
        {
            literal[k++] = line[j];
        }
        literal[k] = '\0';
        char str[256] = {"LITERAL : "};
        strcat(str,literal);
        createToken(token,row_no,i,str);
        i = end_ind;
    }
}


int isKeyword(char *str)
{
    for (int i = 0; i < 16; i++)
    {
        if (strcmp(str, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int isIdentifierChar(char c)
{
    return isalpha(c) || isdigit(c) || c == '_';
}

void getIdentifiers(char line[], int row_no, Token token[256])
{
    int i = 0;
    while (i < strlen(line))
    {
        int x = 0;
        i = isStringLiteral(line, i, &x);
        
        if (!isIdentifierChar(line[i]))
        {
            i++;
            continue;
        }

        int start_ind = i;
        if(isdigit(line[i]) && !isalpha(line[i-1]) && !isalpha(line[i+1]))
        {
            char str[256] = {"NUM:"};
            char digit[2];
            digit[0] = line[i];
            digit[1] = '\0';
            strcat(str,digit);
            createToken(token,row_no,i,str);
            i++;
        }
        else
        {
            while (isIdentifierChar(line[i]))
            {
                i++;
            }
            
            int end_ind = i - 1;

            int identifierLength = end_ind - start_ind + 1;
            char identifier[identifierLength + 1];
            strncpy(identifier, line + start_ind, identifierLength);
            identifier[identifierLength] = '\0';
            char str[256] = {"ID : "};
            strcat(str,identifier);
            if (!isKeyword(identifier))
            {
                createToken(token, row_no, start_ind,str);
            }
        }
        
    }
}



void getKeywords(char line[], int row_no, Token token[256])
{
    int i = 0;
    while (i < strlen(line))
    {
        int x = 0;
        i = isStringLiteral(line, i, &x);
        
        if (!isalpha(line[i]))  // Check for the beginning of a keyword
        {
            i++;
            continue;
        }

        int start_ind = i;
        while (isIdentifierChar(line[i]))
        {
            i++;
        }
        
        int end_ind = i - 1;

        int keywordLength = end_ind - start_ind + 1;
        char keyword[keywordLength + 1];
        strncpy(keyword, line + start_ind, keywordLength);
        keyword[keywordLength] = '\0';
        char str[256] = {"KW : "};
        strcat(str,keyword);
        if (isKeyword(keyword))
        {
            createToken(token, row_no, start_ind,str);
        }
    }
}

void sortTokens(Token *token)
{
    for(int i = 0; i < ind-1; i++)
    {
        for(int j = 0; j < ind-i-1; j++)
        {
            if(token[j].row_no == token[j + 1].row_no)
            {
                if(token[j].col_no > token[j + 1].col_no)
                {
                    Token temp = token[j];
                    token[j] = token[j + 1];
                    token[j + 1] = temp;
                }
            }
        }
    }
}

void getNextToken(Token token[],FILE *fptr1)
{
    char line[256];
    int row_no = 1;
    
    while(fgets(line,256,fptr1))
    {
        getArithOp(line,row_no,token);
        getLogicalOp(line,row_no,token);
        getRelOp(line,row_no,token);
        getStringLiteral(line,row_no,token);
        getIdentifiers(line,row_no,token);
        getKeywords(line,row_no,token);
        getSpecialSymbol(line,row_no,token);
        row_no++;
    }
    sortTokens(token);
    // for(int i = 0; i < ind; i++)
    // {
    //     printf("\n<%s, %d, %d>",token[i].type,token[i].row_no,token[i].col_no);
    // }
}