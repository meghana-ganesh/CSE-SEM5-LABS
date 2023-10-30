%{
	#include<stdio.h>
	#include<stdlib.h>
	#include "q1.tab.h"
%}

%%
\n return NL;
";" return SEMICOLON;
"," return COMMA;
"=" return EQUAL;
"int"|"char"|"bool"|"float" return DATATYPE;
[a-zA-Z]+ return ID;
[0-9]+ return NUMBER;
%%

int yywrap()
{
	return 1;
}