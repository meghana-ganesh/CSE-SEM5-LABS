#include<stdio.h>
#include<stdlib.h>
#include "lex.c"

Token token;
FILE *fp;

void match();
void invalid(char*);
void valid();
void Program();
void declarations();
void datatype();
void identifier_list();
void assign_stat();


void valid()
{
	printf("---SUCCESS!---\n");
	exit(0);
}

void invalid(char *expected)
{
    printf("---ERROR---\n");
    printf("\nerror at row:%d,col:%d",token.row,token.col);
    printf("\nexpected : %s\n",expected);
    exit(0);
}

void match()
{
	token = getNextToken(fp);
}

void datatype()
{
    if(strcmp(token.name,"int") == 0)
        return;
    else if(strcmp(token.name,"char") == 0)
        return;
    else
    {
        invalid("int/char");
    }
}

void identifier_list()
{
    if(strcmp(token.type,"Identifier") == 0)
    {
        match();
        if(strcmp(token.name,",") == 0)
        {
            match();
            identifier_list();
        }
        if(strcmp(token.type,"Identifier") == 0)
        {
            invalid(",");
        }
        else
        {
            return;
        }
    }
    else
    {
        invalid("Identifier");
    }
}

void assign_stat()
{
    if(strcmp(token.type,"Identifier") == 0)
    {
        match();
        if(strcmp(token.name,"=") == 0)
        {
            match();
            if(strcmp(token.type,"Identifier") == 0 || strcmp(token.type,"Number") == 0)
            {
                match();
                if(strcmp(token.name,";") == 0)
                {
                    match();
                    // if(strcmp(token.type,"Identifier") == 0)
                    //     assign_stat();
                    // else
                        return;
                }
                else
                {
                    invalid(";");
                }
            }
            else
            {
                invalid("Identifier/Number");
            }
        }
        else
        {
            invalid("=");
        }
    }
    else
    {
        invalid("Identifier");
    }
}

void declarations()
{
    datatype();
    match();
    identifier_list();
    if(strcmp(token.name,";") == 0)
    {
        match();
        if(strcmp(token.name,"int") == 0 || strcmp(token.name,"char") == 0)
        {
            declarations();
		}
        return;
    }
    else
    {
        invalid(";");
    }
}

void Program()
{
    match();
    if(strcmp(token.name,"main") == 0)
    {
        match();
        if(strcmp(token.name,"(") == 0)
        {
            match();
            if(strcmp(token.name,")") == 0)
            {
                match();
                if(strcmp(token.name,"{") == 0)
                {
                    match();
                    declarations();
                    assign_stat();
                    if(strcmp(token.name,"}") == 0)
                    {
                        return;
                    }
                    else
                    {
                        invalid("}");
                    }
                }
                else
                {
                    invalid("{");
                }
            }
            else
            {
                invalid(")");
            }
        }
        else
        {
            invalid("(");
        }
    }
    else
    {
        invalid("main");
    }
}

int main()
{
	fp = fopen("input.txt","r");
	Program();
	valid();
}


