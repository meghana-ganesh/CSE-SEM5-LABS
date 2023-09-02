#include<stdio.h>
#include<stdlib.h>
void removeSpaces(FILE *fptr1,FILE *fptr2)
{
	char c = fgetc(fptr1);
	while(c != EOF)
	{
		if(c == ' ' || c == '\t')
		{
			fputc(' ',fptr2);
			while((c = fgetc(fptr1)) == ' ' || c == '\t');
			ungetc(c,fptr1);
		}
		else
			fputc(c,fptr2);
		c = fgetc(fptr1);
	}
	printf("spaces removed");
}
//hi      hello