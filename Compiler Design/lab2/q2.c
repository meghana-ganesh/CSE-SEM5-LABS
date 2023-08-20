#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	FILE *fptr1,*fptr2;
	char filename1[100],filename2[100],c,line[1000];

	printf("enter input file:");
	fflush(stdin);
	scanf("%s",filename1);
	printf("enter output file:");
	fflush(stdin);
	scanf("%s",filename2);

	fptr1 = fopen(filename1,"r");
	fptr2 = fopen(filename2,"w+");
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

	fclose(fptr1);
	fclose(fptr2);
	return 0;
}