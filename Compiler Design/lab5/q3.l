%{
	int positive_int = 0;
	int negative_int = 0;
	int positive_float = 0;
	int negative_float = 0;
%}

%%
[+]?[0-9]+ {positive_int++;}
[-]?[0-9]+ {negative_int++;}
[+]?[0-9]+[.][0-9]+ {positive_float++;}
[-]?[0-9]+[.][0-9]+ {negative_float++;}
%%

int main()
{
	yylex();
	printf("+ve int:%d\n-ve int:%d\n+ve float:%d\n-ve float:%d\n",positive_int,negative_int,positive_float,negative_float);
	return 0;
}

int yywrap()
{
	return 1;
}