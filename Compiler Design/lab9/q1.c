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
void statement();
void assign_stat();
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
void looping_stat();
void dprime();
void decision_stat();

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

void assign_stat()
{
    if(strcmp(token.type,"Identifier") == 0)
    {
        match();
        if(strcmp(token.name,"=") == 0)
        {
            match();
            expn();
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

void dprime()
{
    if(strcmp(token.name,"else") == 0)
    {
        match();
        if(strcmp(token.name,"{") == 0)
        {
            match();
            statement_list();
            if(strcmp(token.name,"}") == 0)
            {
                match();
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
        return;
    }
}

void decision_stat()
{
    if(strcmp(token.name,"if") == 0)
    {
        match();
        if(strcmp(token.name,"(") == 0)
        {
            match();
            expn();
            if(strcmp(token.name,")") == 0)
            {
                match();
                if(strcmp(token.name,"{") == 0)
                {
                    match();
                    statement_list();
                    if(strcmp(token.name,"}") == 0)
                    {
                        match();
                        dprime();
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
        invalid("if");
    }
}

void looping_stat()
{
    if(strcmp(token.name,"while") == 0)
    {
        match();
        if(strcmp(token.name,"(") == 0)
        {
            match();
            expn();
            if(strcmp(token.name,")") == 0)
            {
                match();
                if(strcmp(token.name,"{") == 0)
                {
                    match();
                    statement_list();
                    if(strcmp(token.name,"}") == 0)
                    {
                        match();
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
    else if(strcmp(token.name,"for") == 0)
    {
        match();
        if(strcmp(token.name,"(") == 0)
        {
            match();
            assign_stat();
            if(strcmp(token.name,";") == 0)
            {
                match();
                expn();
                if(strcmp(token.name,";") == 0)
                {
                    match();
                    assign_stat();
                    if(strcmp(token.name,")") == 0)
                    {
                        match();
                        assign_stat();
                    }
                    else
                    {
                        invalid(")");
                    }
                }
                else
                {
                    invalid(";");
                }
            }
            else
            {
                invalid(";");
            }
        }
        else
        {
            invalid("(");
        }
    }
    else
        invalid("looping statement");
}

void statement()
{
    if(strcmp(token.type,"Identifier") == 0)
    {
        assign_stat();
        if(strcmp(token.name,";") == 0)
        {
            match();
            return;
        }
        else
        {
            invalid(";");
        }
    }
    else if(strcmp(token.name,"if") == 0)
    {
        decision_stat();
    }
    else if(strcmp(token.name,"while") == 0 || strcmp(token.name,"for") == 0)
    {
        looping_stat();
    }
    else
        return;
    
}

void statement_list()
{
    if(strcmp(token.type,"Identifier") == 0 || strcmp(token.type,"Keyword") == 0)
    {
        statement();
        statement_list();
    }
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


