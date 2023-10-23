%{
    #include <stdio.h>

    int scanf_count = 0;
    int printf_count = 0;
%}

%%
scanf { scanf_count++; fputs("READ",yyout); }
printf { printf_count++; fputs("WRITE",yyout); }
%%

int main(int argc, char* argv[]) 
{
    if (argc != 3) 
    {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    yyout = fopen(argv[2], "w+");

    if (yyin == NULL || yyout == NULL) 
    {
        fprintf(stderr, "Failed to open input or output file.\n");
        return 1;
    }

    yylex();

    fclose(yyin);
    fclose(yyout);

    printf("Number of scanf: %d\n", scanf_count);
    printf("Number of printf: %d\n", printf_count);

    return 0;
}
