%{
    #include<stdio.h>
    #include<stdlib.h>
    #include "q3.tab.h"
%}

%%
[0-9]+ {yylval = atoi(yytext); return NUMBER;}
"*" return '*';
"/" return '/';
"+" return '+';
"-" return '-';
.
[\t\n]
%%

int yywrap()
{
    return 1;
}