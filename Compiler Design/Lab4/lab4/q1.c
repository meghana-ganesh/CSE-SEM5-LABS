#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "getNextToken.h"
typedef struct SymbolTable
{
	int sr_no;
	char lexname[256];
}SymbolTable;

int sind = 0;

void insertSymbolTable(Token token[],SymbolTable stable[],char *str)
{
	stable[sind].sr_no = sind+1;
	strcpy(stable[sind].lexname,str);
	sind++;
}
void KWorID(Token token[],SymbolTable stable[],char *str)
{
	for(int i=0;i<ind;i++)
	{
		char *foundptr = strstr(token[i].type,str);
		if(foundptr)
		{
			char lname[256];
            strcpy(lname, foundptr + 3);

            // Check if lname already exists in the symbol table
            int isDuplicate = 0;
            for (int j = 0; j < sind; j++) 
            {
                if (strcmp(stable[j].lexname, lname) == 0) 
                {
                    isDuplicate = 1;
                    break;
                }
            }

            if (!isDuplicate) 
            {
                insertSymbolTable(token, stable, lname);
            }
		}

	}
}
void createSymbolTable(Token token[],SymbolTable stable[])
{
	KWorID(token,stable,"ID");
	KWorID(token,stable,"KW");
}
int main()
{
	Token token[256];
	SymbolTable stable[256];
	FILE *fptr1 = fopen("file1.txt","r");
    if(fptr1 == NULL)
    {
        printf("\nERROR:File not opened!");
        exit(0);
    }
	getNextToken(token,fptr1);
    createSymbolTable(token,stable);
    for(int i=0;i<sind;i++)
    {
    	printf("\nSYMBOLTABLE: %d %s",stable[i].sr_no,stable[i].lexname);
    }
   	fclose(fptr1);
    return 0;
}