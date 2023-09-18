#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int curr = 0;
char str[100];
void T();
void S();
void Tprime();
void invalid()
{
	printf("-----------------ERROR!----------------\n");
	exit(0);
}
void valid()
{
	printf("----------------SUCCESS!---------------\n");
	exit(0);
}
void Tprime()
{
	if(str[curr] == ',')
	{
		curr++;
		S();
		Tprime();
	}
}

void T()
{
	if(str[curr] == 'a')
	{
		curr++;
		Tprime();
	}
	else if(str[curr] == '>')
	{
		curr++;
		Tprime();
	}
	else if(str[curr] == '(')
	{
		curr++;
		T();
		if(str[curr] == ')')
		{
			curr++;
			Tprime();
		}
		else
			invalid();
	}
	else
		invalid();
}
void S()
{
	if(str[curr] == 'a')
	{
		curr++;
		return;
	}
	else if(str[curr] == '>')
	{
		curr++;
		return;
	}
	else if(str[curr] == '(')
	{
		curr++;
		T();
		if(str[curr] == ')')
		{
			curr++;
			return;
		}
		else
			invalid();
	}
	else
		invalid();

}

int main()
{
	printf("enter string:");
	scanf("%s",str);
	S();
	if(str[curr] == '$')
	valid();
	else
	// printf("%c\n", str[curr]);
	invalid();
}

//S->a|>|(T)
//T->T,S|S
//A->Ax|B

//A->BA'
//A'-> xA'|e


//S->a|>|(T)
//T->ST'|S
//T'-> ,ST'|e