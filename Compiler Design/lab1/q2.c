#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *fptr1,*fptr2;
	char filename[100],filename1[100],c;

	printf("enter filename1:");
	fflush(stdin);
	scanf("%s",filename);
	printf("enter filename2:");
	fflush(stdin);
	scanf("%s",filename1);

	fptr1 = fopen(filename,"r");
	fptr2 = fopen(filename1,"w+");

	fseek(fptr1,0L,SEEK_END);
	long int size = ftell(fptr1);
	printf("the size of the file is:%ld bytes",size);

	fseek(fptr1,0,SEEK_SET);
	long int pos = size-1;//do size-2 to prevent extra line in the biginning cuz it is reading '\n' as well
	while(pos >= 0)
	{
		fseek(fptr1,pos,SEEK_SET);
		c = fgetc(fptr1);
		fputc(c,fptr2);
		pos--;
	}
	printf("\ncontents copied to %s",filename1);
	fclose(fptr1);
	fclose(fptr2);
	return 0;
}