%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
extern FILE* yyin;
%}

%token PLUS MINUS MUL DIV EXPO N NL NUM

%%
input: input line
	| 
	;
line: NL
	| exp NL
	;
exp: NUM
	| exp exp PLUS
	| exp exp MINUS
	| exp exp EXPO
	| exp exp MUL
	| exp exp DIV
	| exp exp N
	;
%%

int yyerror(){
	printf("Invalid\n");
	exit(0);
}

int main(){
	char name[100];
	printf("Enter file name: ");
	scanf("%s",name);
	yyin=fopen(name,"r");
	do{
		if(yyparse()){
			printf("Failure\n");
			exit(0);
		}
	}while(!feof(yyin));
	printf("Success\n");
}