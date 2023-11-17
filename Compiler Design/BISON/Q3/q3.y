%{
    #include<stdio.h>
    #include<stdlib.h>
    int yyerror();
    int yylex();
    extern FILE *yyin;
%}

%token NUMBER
%left '+' '-'
%left '/' '*'

%%
E : T {printf("result:%d\n",$$);};
T : T '+' T {$$ = $1 + $3;}
    | T '-' T {$$ = $1 - $3;}
    | T '*' T {$$ = $1 * $3;}
    | T '/' T {$$ = $1 / $3;}
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
    yyin = fopen("input3.txt","r");
    do
    {
        if(yyparse())
        {
            printf("Failure");
            exit(1);
        }
    }while(!feof(yyin));
    printf("success");
    return 0;
}
