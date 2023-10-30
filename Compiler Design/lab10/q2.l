%{
	#include<stdio.h>
	#include<stdlib.h>
	int yylex();
	int yyerror();
	extern FILE* yyin;
%}

%token IF OPENBRACKET CLOSEBRACKET ELSE OPENBRACE CLOSEBRACE
%start program

%%
program:ifstmt elseifstmt elsestmt
if:IF OPENBRACKET expn CLOSEBRACKET openbrace closebrace

%%

int yyerror()
{

}
