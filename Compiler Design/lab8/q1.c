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
void statement_list();
void identifier_list();
int statement();
int assign_stat();
void expn();
void eprime();
void simple_exp();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();

void valid()
{
    printf("\n---SUCCESS---");
    exit(0);
}

void invalid(char *expected)
{
    printf("\n---ERROR---");
    printf("\nerror at row:%d,col:%d",token.row,token.col);
    printf("\nexpected : %s",expected);
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
        else if(strcmp(token.name,"[") == 0)
        {
            match();
            if(strcmp(token.type,"Number") == 0)
            {
                match();
                if(strcmp(token.name,"]") == 0)
                {
                    match();
                    if(strcmp(token.name,",") == 0)
                    {
                        match();
                        identifier_list();
                    }
                    else if(strcmp(token.type,"Identifier") == 0)
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
                    invalid("]");
                }
            }
            else
            {
                invalid("Number");
            }
        }
        if(strcmp(token.type,"Identifier") == 0)
        {
            invalid(",");
        }
        else if(strcmp(token.type,"Number") == 0)
        {
            invalid("[");
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

void factor()
{
    if(strcmp(token.type,"Identifier") == 0)
    {
        return;
    }
    else if(strcmp(token.type,"Number") == 0)
    {
        return;
    }
    else
    {
        invalid("Identifier/Number");
    }
}

void addop()
{
    if(strcmp(token.name,"+") == 0)
    {
        return;
    }
    else if(strcmp(token.name,"-") == 0)
    {
        return;
    }
    else
    {
        invalid("+/-");
    }
}

void mulop()
{
    if(strcmp(token.name,"*") == 0)
    {

        return;
    }
    else if(strcmp(token.name,"/") == 0)
    {
        return;
    }
    else if(strcmp(token.name,"%") == 0)
    {
        return;
    }
    else
    {
        invalid("* or / or %");
    }
}

int ismulop(char *str)
{
    if(strcmp(str,"*") == 0)
    {
        return 1;
    }
    else if(strcmp(str,"/") == 0)
    {
        return 1;
    }
    else if(strcmp(str,"%") == 0)
    {
        return 1;
    }
    return 0;
}

int isaddop(char *str)
{
    if(strcmp(str,"+") == 0)
    {
        return 1;
    }
    else if(strcmp(str,"-") == 0)
    {
        return 1;
    }
    return 0;
}

void tprime()
{
    if(ismulop(token.name))
    {
        mulop();
        match();
        factor();
        match();
        tprime();
    }
    else
    {
        return;
    }
}

void seprime()
{
    if(isaddop(token.name))
    {
        addop();
        match();
        term();
        seprime();
    }
    else
    {
        return;
    }
}

void term()
{
    factor();
    match();
    tprime();
}

void simple_exp()
{
    term();
    seprime();
}

void relop()
{
    if(strcmp(token.name,">=") == 0)
    {
        match();
        return;
    }
    else if(strcmp(token.name,"<=") == 0)
    {
        match();
        return;
    }
    else if(strcmp(token.name,"==") == 0)
    {
        match();
        return;
    }
    else if(strcmp(token.name,"!") == 0)
    {
        match();
        return;
    }
    else if(strcmp(token.name,"=") == 0)
    {
        match();
        return;
    }
    else if(strcmp(token.name,">") == 0)
    {
        match();
        return;
    }
    else if(strcmp(token.name,"<") == 0)
    {
        match();
        return;
    }
    else
        invalid("Relational Operator");
}

int isrelop(char *str)
{
    if(strcmp(str,"=") == 0)
    {
        return 1;
    }
    else if(strcmp(str,">") == 0)
    {
        return 1;
    }
    else if(strcmp(str,"<") == 0)
    {
        return 1;
    }
    else if(strcmp(str,"!") == 0)
    {
        return 1;
    }
    else if(strcmp(token.name,">=") == 0)
    {
        return 1;
    }
    else if(strcmp(token.name,"<=") == 0)
    {
        return 1;
    }
    else if(strcmp(token.name,"==") == 0)
    {
        return 1;
    }
    return 0;
}

void eprime()
{
    if(isrelop(token.name))
    {
        relop();
        simple_exp();
    }
    else
    {
        return;
    }
}

void expn()
{
    simple_exp();
    eprime();
}

int assign_stat()
{
    if(strcmp(token.type,"Identifier") == 0)
    {
        match();
        if(strcmp(token.name,"=") == 0)
        {
            match();
            expn();
            return 1;
        }
        else
        {
            invalid("=");
        }
    }
    return 0;
}

int statement()
{
    int x = assign_stat();
    if(x == 1)
    {
        if(strcmp(token.name,";") == 0)
        {
            match();
            return x;
        }
        else
        {
            invalid(";");
        }
    }
    else
        return 0;
}

void statement_list()
{
    int x = statement();
    if(x == 1)
        statement_list();
    else
        return;
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
                    statement_list();
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


