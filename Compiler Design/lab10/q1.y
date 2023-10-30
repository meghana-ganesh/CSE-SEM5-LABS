%{
	#include<stdio.h>
	#include<stdlib.h>
	int yylex();
	int yyerror();
	extern FILE *yyin;
%}

%token DATATYPE ID NL SEMICOLON COMMA EQUAL NUMBER
%start program

%%
program:declaration SEMICOLON NL {printf("Valid"); exit(0);}
		;
declaration:DATATYPE idlist
			| DATATYPE ID EQUAL ID
			| DATATYPE ID EQUAL NUMBER;
			;
idlist: ID
		| ID COMMA idlist
		;
%%

int yyerror(char *msg)
{
	printf("Invalid expression\n");
	return 1;
}

void main()
{
	printf("Enter expression:\n");
	yyparse();
}
