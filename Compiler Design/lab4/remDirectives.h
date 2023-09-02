#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void remDirectives(FILE *fptr1,FILE *fptr2)
{
    char line[1000];
    while(fgets(line,sizeof(line),fptr1))
	{
		if(strstr(line,"\"") || strstr(line,"\'"))
		{
			fputs(line,fptr2);
			continue;
		}
		if(line[0] == '#' || (line[0] == ' ' && line[1] == '#'))
			continue;
		fputs(line,fptr2);
	}
}