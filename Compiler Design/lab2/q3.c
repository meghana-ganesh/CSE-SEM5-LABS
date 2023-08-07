#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
int main()
{
	FILE *fptr1,*fptr2;
	char filename1[100],filename2[100],line[1000],*ret;

	printf("enter input file:");
	fflush(stdin);
	scanf("%s",filename1);
	printf("enter output file:");
	fflush(stdin);
	scanf("%s",filename2);

	fptr1 = fopen(filename1,"r");
	fptr2 = fopen(filename2,"w+");

	char keywords[32][20] = 
	{
		"auto", "break", "case", "char", "const", "continue", "default", "do", "double",
	    "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
	    "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
	    "union", "unsigned", "void", "volatile", "while"
	};
	while(fgets(line,sizeof(line),fptr1))
	{
		char *token = strtok(line," ");
		printf("tokens: %s \n",token);
	}
	fclose(fptr1);
	fclose(fptr2);
	return 0;
}