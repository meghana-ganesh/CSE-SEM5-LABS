%{
    #include<stdio.h>
    #include<stdlib.h>
    #include "q2.tab.h"
%}

%%
"if" return IF;
"else" return ELSE;
[0-9]+ return NUMBER;
[a-zA-Z][a-zA-Z0-9_]* return ID;
";" return SEMICOLON;
"=" return EQUAL;
"+" return ADDOP;
"-" return ADDOP;
"*" return MULOP;
"/" return MULOP;
"%" return MULOP;
"(" return OPENBR;
")" return CLOSEBR;
"{" return OPENBRACE;
"}" return CLOSEBRACE;
">" return RELOP;
"<" return RELOP;
">=" return RELOP;
"<=" return RELOP;
"==" return RELOP;
"!=" return RELOP;
.   
[\t\n]
%%

int yywrap()
{
    return 1;
}