%{
    int word_count = 0;
    int char_count = 0;
    int blank_count = 0;
    int line_count = 0;
%}

%%
[a-zA-Z]+      { word_count++; char_count += yyleng; }
[ \t]+         { blank_count++; char_count += yyleng; }
\n             { line_count++; char_count++; }
.              { char_count++; }
%%

int main() 
{
    yylex();
    printf("Words: %d\nCharacters: %d\nBlanks: %d\nLines: %d\n", word_count, char_count, blank_count, line_count);
    return 0;
}

int yywrap()
{
    return 1;
}
