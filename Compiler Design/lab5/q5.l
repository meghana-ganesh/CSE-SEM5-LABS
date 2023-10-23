%{
#include <stdio.h>
%}

%%
[0-9]+ {
    int decimal = atoi(yytext);
    printf("Decimal: %d, Hexadecimal: 0x%x\n", decimal, decimal);
}
. ; // Ignore other characters
%%

int main() 
{
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
