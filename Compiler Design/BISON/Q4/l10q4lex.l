%{
#include<stdio.h>
#include<stdlib.h>
#include"l10q4b.tab.h"
%}

%%
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
"^" {return EXPO;}
"n" {return N;}
[\n] {return NL;}
[0-9]+ {return NUM;}
%%

int yywrap(){
	return 1;
}