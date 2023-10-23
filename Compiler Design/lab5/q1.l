%{
    int vowel_count = 0;
    int consonant_count = 0;
%}

%%
[aAeEiIoOuU]   { vowel_count++; }
[a-zA-Z]        { consonant_count++; }
.              ;  // Ignore other characters
%%

int main() 
{
    yylex();
    printf("Vowels: %d\nConsonants: %d\n", vowel_count, consonant_count);
    return 0;
}

int yywrap()
{
    return 1;
}