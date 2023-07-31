#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *fptr1,*fptr2,*fptr3;
	char filename1[100],filename2[100],filename3[100],c1,c2;
	printf("enter filename1:");
	fflush(stdin);
	scanf("%s",filename1);
	printf("enter filename2:");
	fflush(stdin);
	scanf("%s",filename2);
	printf("enter filename3:");
	fflush(stdin);
	scanf("%s",filename3);

	fptr1 = fopen(filename1,"r");
	fptr2 = fopen(filename2,"r");
	fptr3 = fopen(filename3,"w+");

	c1 = fgetc(fptr1);
	c2 = fgetc(fptr2);
	fputc(c1,fptr3);
	int count = 1;

	while(c1 != EOF || c2 != EOF)
	{
		c1 = fgetc(fptr1);
		while(c1 != EOF && c1 != '\n')
		{
			fputc(c1,fptr3);
			c1 = fgetc(fptr1);
		}
		if(count == 1)
		{
			fputc(c2,fptr3);
			count = 0;
		}
		c2 = fgetc(fptr2);
		while(c2 != EOF && c2 != '\n')
		{
			fputc(c2,fptr3);
			c2 = fgetc(fptr2);
		}
	}

	printf("\ncopy done");
	fclose(fptr1);
	fclose(fptr2);
	fclose(fptr3);
	return 0;
}