%{
    #include<stdio.h>
    #include<stdlib.h>
    int yylex();
    int yyerror();
    extern FILE *yyin;
%}

%token DATATYPE ID NUMBER NL COMMA SQOPEN SQCLOSE SEMICOLON

%%
program:declarations
declarations: DATATYPE idlist SEMICOLON newline declarations 
            | 
            ;
newline: NL
        |
        ;
idlist: ID 
        | ID COMMA idlist 
        | ID SQOPEN NUMBER SQCLOSE 
        | ID SQOPEN NUMBER SQCLOSE COMMA idlist;
%%

int yyerror(char *msg)
{
    printf("Invalid expression:%s\n",msg);
    return 1;
}

void main()
{
    yyin = fopen("input1.txt","r");
    do
    {
        if(yyparse())
        {
            printf("Failure\n");
            exit(0);
        }
    }while(!feof(yyin));
    printf("success");
}
