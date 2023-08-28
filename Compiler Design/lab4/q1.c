#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "getNextToken.h"
#define tbsize 30
typedef struct SymbolTable
{
	int sr_no;
	char lexname[256];
    char retType[256];
    char dataType[256];
    char nature[256];
    int argc;
}SymbolTable;


int sind = 0;

int Hashfunc(char *str)
{
    int sum = 0;
    for(int i=0;i<strlen(str);i++)
    {
        sum += str[i];
    }
    return sum % tbsize;
}
void inserttoST(Token token[],SymbolTable stable[],char *lexname,char *retType,char *dataType,char *nature,int argc)
{
    int val = Hashfunc(lexname);
    if(strcmp(stable[val].lexname,lexname) != 0)
    {
        if(stable[val].lexname != 0)
        {
            while(stable[val].lexname[0] != 0)
            {
                val++;
            }
        }
        stable[val].sr_no = sind;
        strcpy(stable[val].lexname,lexname);
        strcpy(stable[val].retType,retType);
        strcpy(stable[val].dataType,dataType);
        strcpy(stable[val].nature,nature);
        stable[val].argc = argc;
        sind++;    
    }
}

void displayST(SymbolTable stable[])
{
    for(int i=0;i<tbsize;i++)
    {
        if (stable[i].lexname[0] != '\0') 
        {
            printf("\nSYMBOLTABLE: %d %s %s %s %s %d",stable[i].sr_no,stable[i].lexname,stable[i].retType,stable[i].dataType,stable[i].nature,stable[i].argc);
        }
    }
}

void readToken(Token token[],SymbolTable stable[])
{
    for(int i=0;i<ind;i++)
    {
        int flag = 0;
        if(strcmp(token[i].type,"ID") == 0)
        {
            if((i+2<ind) && (i-1>=0) && (strcmp(token[i+1].name,"(") == 0) && (strcmp(token[i-1].type,"KW") == 0))
            {
                flag = 1;
                int closeind = i+2;
                int count = 0;
                int argc;
                while(strcmp(token[closeind].name,")") != 0)
                {
                    if(strcmp(token[closeind].type,"KW") == 0)
                    {
                        count++;
                    }
                    closeind++;
                }
                inserttoST(token,stable,token[i].name,token[i-1].name,"NIL","FUNC",count);
                i = closeind + 1;
            }
        }
        // else if(flag == 0 && strcmp(token[i].type,"KW") == 0)
        // {
        //     char* retType = token[i].name;
        //     if(i+1<ind && strcmp(token[i+1].type,"ID") == 0)
        //     {
        //         int closeind = i+1;
        //         inserttoST(token,stable,token[i+1].name,"NIL",retType,"VAR",0);
        //         while(strcmp(token[closeind].name,";") != 0)
        //         {
        //             if(strcmp(token[closeind].type,"ID") == 0)
        //             {
        //                 inserttoST(token,stable,token[closeind].name,"NIL",retType,"VAR",0);
        //             }
        //             closeind++;
        //         }
        //         i = closeind + 1;
        //     }
        // }
    }
}



int main()
{
 Token token[256];
 SymbolTable stable[tbsize];
 FILE *fptr1 = fopen("file1.txt","r");
    if(fptr1 == NULL)
    {
        printf("\nERROR:File not opened!");
        exit(0);
    }
    getNextToken(token,fptr1);
    readToken(token,stable);
    displayST(stable);
    fclose(fptr1);
    return 0;
}