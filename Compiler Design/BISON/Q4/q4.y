%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<math.h>
    int yyerror();
    int yylex();
    extern FILE *yyin;
%}

%token NUMBER
%left '+' '-'
%left '/' '*'
%right '^'

%%
input: input line 
    | {printf("result:%d",$$);}
    ;

line: '\n'
    | exp '\n'
    ;

exp:exp exp '+' { $$ = $1 + $2; printf("%d\n",$$);}
   | exp exp '-' { $$ = $1 - $2; }
   | exp exp '*' { $$ = $1 * $2; }
   | exp exp '/' { $$ = $1 / $2; }
   | exp exp '^' { $$ = $1 ^ $2; }
   | exp 'n' { $$ = $-1; }
   | NUMBER {$$ = $1;}
   ;

%%

int yyerror(char *msg)
{
    printf("Invalid expression:%s",msg);
    exit(1);
}

int main()
{
    yyin = fopen("input4.txt","r");
    if(yyparse())
    {
        printf("Failure");
        exit(1);
    }
    printf("success");
    return 0;
}