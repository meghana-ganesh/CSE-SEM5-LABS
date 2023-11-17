%{
    #include<stdio.h>
    #include<stdlib.h>
    #include "q4.tab.h"
%}

%%
[0-9] {yylval = atoi(yytext); return NUMBER;}
\n return '\n';
"+" return '+';
"*" return '*';
"/" return '/';
"-" return '-';
"^" return '^';
"n" return 'n';
%%

int yywrap()
{
    return 1;
}