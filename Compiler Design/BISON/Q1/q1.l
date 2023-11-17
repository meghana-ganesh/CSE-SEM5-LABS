%{
    #include<stdio.h>
	#include<stdlib.h>
	#include "q1.tab.h"
%}

%%
"\n" return NL;
";" return SEMICOLON;
"," return COMMA;
"int" return DATATYPE;
"char" return DATATYPE;
"[" return SQOPEN;
"]" return SQCLOSE;
[0-9]+ return NUMBER;
[a-zA-Z_]+ return ID;
%%

int yywrap()
{
    return 1;
}