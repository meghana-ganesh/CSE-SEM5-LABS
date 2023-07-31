#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *fptr;
	char filename[100],c;
	int count_char = 0,count_end = 0;
	printf("enter filename:");
	fflush(stdin);
	scanf("%s",filename);
	fptr = fopen(filename,"r");
	c = fgetc(fptr);
	while(c!=EOF)
	{
		c = fgetc(fptr);
		if(c == '\n')
			count_end++;
		count_char++;
	}
	printf("no. of characters:%d",count_char);
	fclose(fptr);
	printf("\nno. of lines are:%d",count_end);
	return 0;
}