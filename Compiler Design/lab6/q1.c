#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int isSymbol(char c)
{
	char symbols[5] = {'*','+',',','(',')'};
	for(int i=0;i<5;i++)
	{
		if(symbols[i] == c)
			return 1;
	}
	return 0;
}
void remLeftRecursion(FILE *fptr1,FILE *fptr2)
{
	char line[256];
	while(fgets(line,256,fptr1))
	{
		char *A;
		char *x;
		char *B;
		char c = line[0];
		int n = strlen(line);
		for(int i=2;i<n;i++)
		{
			if(line[i] == c)
			{
				if((line[i+1] == '|' || isalpha(line[i+1]) || line[i+1]) && i+1<n && !isalpha(line[i-1]))
				{

				}
			}
		}
	}
}
int main()
{
	FILE *fptr1 = fopen("file1.txt","r");
	FILE *fptr2 = fopen("file2.txt","w+");
	remLeftRecursion(fptr1,fptr2);
	fclose(fptr1);
	fclose(fptr2);
}
//S->a|>|(T)
//T->T,S|S
//A->Ax|B
//A->BA'
//A'-> xA'|e


// S->UVW
// U ->(S) | aSb | d
// V -> aV | 𝜖
// W -> cW | 𝜖

// 3. S->aAcBe
// A->Ab|b
// B->d