#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int cur = 0;
char str[100];

void S();
void V();
void W();

void valid()
{
	printf("-----SUCCESS----");
	exit(1);
}

void invalid()
{
	printf("-----ERROR-----");
	exit(1);
}

void W()
{
	if(str[cur] == 'c')
	{
		cur++;
		W();
	}
}

void V()
{
	if(str[cur] == 'a')
	{
		cur++;
		V();
	}
}


void U()
{
	if(str[cur] == '(')
	{
		cur++;
		S();
		if(str[cur] == ')')
		{
			cur++;
			return;
		}
		else
			invalid();
	}
	else if(str[cur] == 'a')
	{
		cur++;
		S();
		if(str[cur] == 'b')
		{
			cur++;
			return;
		}
		else
			invalid();
	}
	else if(str[cur] == 'd')
	{
		cur++;
		return;
	}
	else
		invalid();
}

void S()
{
	U();
	V();
	W();
}

int main()
{
	printf("enter string:");
	scanf("%s",str);
	S();
	if(str[cur] == '$')
		valid();
	else
		invalid();
}

// S->UVW
// U ->(S) | aSb | d
// V ->aV | 𝜖
// W ->cW | 𝜖