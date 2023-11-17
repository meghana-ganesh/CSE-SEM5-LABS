%{
    #include <stdio.h>
    #include <stdlib.h>
    int yylex();
    int yyerror(char*);
    extern FILE* yyin;
%}

%token IF OPENBR ID MULOP RELOP NUMBER CLOSEBR OPENBRACE CLOSEBRACE ELSE EQUAL SEMICOLON ADDOP
%left MULOP
%left ADDOP

%%
program: decision_stat program
        |
        ;

decision_stat: if 
            | if else
            | if elseif else
            | if elseif
            ;
nested:decision_stat
        |
        ;

if: IF OPENBR exprn CLOSEBR OPENBRACE statement_list nested statement_list CLOSEBRACE
   ;
else: ELSE OPENBRACE statement_list nested statement_list CLOSEBRACE
    ;

elseif: ELSE if
    ;

exprn: ID RELOP ID
    | ID RELOP NUMBER
    | ID
    ;

statement_list : statement statement_list
                |
                ;

statement : assign_stat SEMICOLON;

assign_stat : ID EQUAL expr;

expr : simple_expn eprime;

eprime : in_eprime 
        |
        ;
in_eprime : RELOP simple_expn;

simple_expn : term seprime;

term : factor tprime;

seprime : in_seprime
        |
        ;

in_seprime : ADDOP term seprime;

tprime : in_tprime
        |
        ;
in_tprime : MULOP factor tprime;

factor : ID 
        | NUMBER
        ;

%%

int yyerror(char *msg)
{
    printf("Invalid Expression: %s\n",msg);
    exit(1);
}

int main()
{
    yyin = fopen("input.txt","r");
    do
    {
        if (yyparse())
        {
            printf("Failure");
            exit(1);
        }
    } while (!feof(yyin));
    printf("success");
    return 0;
}
