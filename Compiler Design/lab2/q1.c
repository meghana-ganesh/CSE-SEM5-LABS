#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *fptr1,*fptr2;
	char filename1[100],filename2[100],c;

	printf("enter filename1:");
	fflush(stdin);
	scanf("%s",filename1);
	printf("enter filename2:");
	fflush(stdin);
	scanf("%s",filename2);
	fptr1 = fopen(filename1,"r");
	fptr2 = fopen(filename2,"w+");
	c = fgetc(fptr1);
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
	fclose(fptr1);
	fclose(fptr2);
	return 0;
}
//hi      hello