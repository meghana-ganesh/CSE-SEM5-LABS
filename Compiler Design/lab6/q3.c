#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char str[100];
int cur = 0;

void invalid()
{
	printf("---ERROR---");
	exit(0);
}
void valid()
{
	printf("---SUCCESS---");
	exit(0);
}

void B()
{
	if(str[cur] == 'd')
	{
		cur++;
		return;
	}
	else
		invalid();
}

void Aprime()
{
	if(str[cur] == 'b')
	{
		cur++;
		Aprime();
	}
}

void A()
{
	if(str[cur] == 'b')
	{
		cur++;
		Aprime();
	}
	else
		invalid();
}

void S()
{
	if(str[cur] == 'a')
	{
		cur++;
		A();
		if(str[cur] == 'c')
		{
			cur++;
			B();
			if(str[cur] == 'e')
			{
				cur++;
				return;
			}
			else
				invalid();
		}
		else
			invalid();
	}
	else
		invalid();
}


int main()
{
	printf("enter the string:");
	scanf("%s",str);
	S();
	if(str[cur] == '$')
		valid();
	else
		invalid();
}
// S->aAcBe
// A->Ab|b
// B->d


//A -> Ab|b

//A->Ax|B
//A->BA'
//A'-> xA'|e

//A->bA'
//A'-> bA'|e

//S->aAcBe
//A->bA'
//A'->bA'|e
//B->d