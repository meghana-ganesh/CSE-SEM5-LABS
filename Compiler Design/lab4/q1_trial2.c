
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "getNextToken.h"
#include "remDirectives.h"
#include "removespaces.h"
#include "remComments.h"
#define tbsize 30
typedef struct SymbolTable
{
	int index;
	char lexname[256];
    char returnType[256];
    char dataType[256];
    char tokenType[256];
    int argc;
}SymbolTable;

struct ListElement
{
    struct SymbolTable tkn;
    struct ListElement* next;
};

struct ListElement *TABLE[30];

int currInd = 1;

void Initialize()
{
    for(int i=0;i<30;i++)
    {
        TABLE[i] = NULL;
    }
}

int hash(char* str)
{
    int sum = 0;
    for(int i=0;i<strlen(str);i++)
    {
        sum += str[i];
    }
    return sum % 30;
}

int search(char* str)
{

    int val = hash(str);
    if(TABLE[val] == NULL)
        return 0;
    else
    {

        struct ListElement* cur = TABLE[val];
        while(cur)
        {
            if(strcmp(cur->tkn.lexname,str) == 0)
                return 1;
            cur = cur->next;
        }
    }
    return 0;
}

void display()
{
    printf("SL.NO\tLEX_NAME\tRET_TYPE\tDAT_TYPE\tTOK_TYPE\tARGC\n");
    for(int i=0;i<30;i++)
    {
        if(TABLE[i] == NULL)
            continue;
        else
        {
            struct ListElement * ele= TABLE[i];
            while(ele)
            {
                printf("%d\t%s\t\t%s\t\t%s\t\t%s\t\t%d\n",ele->tkn.index,ele->tkn.lexname,ele->tkn.returnType,ele->tkn.dataType,ele->tkn.tokenType,ele->tkn.argc);
                ele = ele->next; 
            }   
        }
    }
}

void insert(SymbolTable tk)
{   

    if(search(tk.lexname)==1)
    {

        return; 
    }

    int val = hash(tk.lexname);
    struct ListElement* cur =(struct ListElement*)malloc(sizeof(struct ListElement));
    cur->tkn = tk;
    cur->next = NULL;
    if(TABLE[val]==NULL)
    {

        TABLE[val] = cur;
    }
    else
    {
        struct ListElement * ele= TABLE[val];
        while(ele->next!=NULL)
        {
            ele = ele->next; 
        }
        ele->next = cur;
    }
}
const char *ReturnTypes[] = {"int","float","char","void"};
const char *PredefFuncs[] = {"printf","scanf"};

int isReturnType(const char *str)
{
    for (int i = 0; i < sizeof(ReturnTypes) / sizeof(char *); i++)
    {
        if (strcmp(str, ReturnTypes[i]) == 0)
            return 1;
    }
    return 0;
}

int isPredefFuncs(const char *str)
{
    for (int i = 0; i < sizeof(PredefFuncs) / sizeof(char *); i++)
    {
        if (strcmp(str,PredefFuncs[i]) == 0)
            return 1;
    }
    return 0;
}

void insertToST(Token token,char* type,char* recTypetkn,int argc)
{

    SymbolTable tkn;
    tkn.index = token.index;
    strcpy(tkn.lexname,token.name);
    if(isPredefFuncs(token.name))
    {
        tkn.argc = argc;
        strcpy(tkn.returnType,"int");
        strcpy(tkn.tokenType,type);
        strcpy(tkn.dataType,"-");
        insert(tkn);
    }
    if(strstr(token.type,"ID"))
    {
        if(strcmp(type,"VAR") == 0)
        {
            tkn.argc = 0;
            strcpy(tkn.returnType,"-");
            strcpy(tkn.tokenType,type);
            strcpy(tkn.dataType,recTypetkn);
            insert(tkn);
        }
        else
        {
            tkn.argc = argc;
            strcpy(tkn.returnType,recTypetkn);
            strcpy(tkn.tokenType,type);
            strcpy(tkn.dataType,"-");

            insert(tkn);

        }
    }
}

void printToken(Token* token)
{
    if(strstr(token->type,"ID"))
    {
        char id[10];
        if(search(token->name) == 0){
            token->index = currInd;
            currInd++;
        }
        else{
            struct ListElement* cur = TABLE[hash(token->name)];
            while(cur){
                if(strcmp(cur->tkn.lexname,token->name) == 0){
                    token->index = cur->tkn.index;
                    break;
                }
                cur = cur->next;
            }
        }
        sprintf(id,"ID%d",token->index);
        printf("\n<%s, %d, %d>",id,token->row_no,token->col_no);
    }
    else
    {
        printf("\n<%s, %d, %d>",token->name,token->row_no,token->col_no);
    }
}


int main()
{
    Token token[256];
    FILE *fptr1 = fopen("file1.txt","r");
    FILE *fptr2 = fopen("file3.txt","w+");
    FILE *fptr3 = fopen("file4.txt","w+");
    FILE *fptr4 = fopen("file5.txt","w+");
	removeSpaces(fptr1,fptr2);
    fclose(fptr2);
    fptr2 = fopen("file3.txt","r");
    remDirectives(fptr2,fptr3);
    fclose(fptr3);
    fptr3 = fopen("file4.txt","r");
    removeComments(fptr3,fptr4);
    fclose(fptr4);
    fptr4 = fopen("file5.txt","r");
    if(fptr4 == NULL)
    {
        printf("\nERROR:File not opened!");
        exit(0);
    }
    getNextToken(token,fptr4);
    // readToken(token,stable);
    // displayST(stable);
    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);
    fclose(fptr4);
    char recTypetkn[20];
    Token prevtkn;
    int index = 1;
    int argc = 0;
    char id[10];
    char temp[20];
    Initialize();
    int i = 0;
    while(i<ind)
    {
        printToken(&token[i]);

        //Symbol Table
        if(isReturnType(token[i].name))
        {
            strcpy(recTypetkn,token[i].name);
        }
        if(strstr(prevtkn.type,"ID"))
        {
            if(strcmp(token[i].name,"(") == 0)
            {
                i++;
                if(strcmp(token[i].name,")")==0 && i<ind)
                {
                    printToken(&token[i]);
                    argc = 0;
                }
                else
                {
                    argc = 1;
                    while(strcmp(token[i].name,")")!=0 && i<ind)
                    {
                        printToken(&token[i]);
                        if(isReturnType(token[i].name))
                        {
                            strcpy(temp,token[i].name);
                        }
                        insertToST(token[i],"VAR",temp,0);
                        if(strcmp(token[i].name,",") == 0)
                        {
                            argc++;
                        }
                        i++;
                    }
                    printToken(&token[i]);
                }
                insertToST(prevtkn,"FUNC",recTypetkn,argc);
            }
            else
            {
                insertToST(prevtkn,"VAR",recTypetkn,0);
            }
        }
        prevtkn = token[i];
        i++;
    }
    printf("\n");
    display();
    return 0;
}