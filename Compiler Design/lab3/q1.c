#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct Token
{
	char type[10];
	char c;
	int row;
	int col;
}Token;

void removearithop(FILE *fptr1,FILE *fptr2)
{
	Token tp[10];
	char c = fgetc(fptr1);
	char x,y;
	int i=0;
	int ind=0;
	int lncount = 1;
	while(c != EOF)
	{
		if(c == '+'|| c == '-' || c == '*' || c == '/' || c == '%')
		{
				x = fgetc(fptr1);
				if(isalnum(x))
				{
					strcpy(tp[ind].type,"arithop");
					tp[ind].c = c;
					tp[ind].col = i;
					tp[ind].row = lncount;
					ind++;
				}
				else if(x == ' ')
				{
					y = fgetc(fptr1);
					if(isalnum(y))
					{
						strcpy(tp[ind].type,"arithop");
						tp[ind].c = c;
						tp[ind].col = i;
						tp[ind].row = lncount;
						ind++;
					}
				}
		}
		if(c == '\n')
		{
			lncount++;
			int i=0;
		}
		i++;
		c = fgetc(fptr1);
	}
	for(int i=0;i<ind;i++)
	{
		printf("\ntype:%s:%c,row:%d,col:%d",tp[i].type,tp[i].c,tp[i].row,tp[i].col);
	}
}
int main()
{
	FILE *fptr1,*fptr2;
	char filename1[100],filename2[100];
	printf("enter input filename:");
	fflush(stdin);
	scanf("%s",filename1);

	printf("enter output filename:");
	fflush(stdin);
	scanf("%s",filename2);

	fptr1 = fopen(filename1,"r");
	fptr2 = fopen(filename2,"w");
	removearithop(fptr1,fptr2);
	// removelogicop(fptr1,fptr2);
	fclose(fptr1);
	fclose(fptr2);
	return 0;
}