void removeComments(FILE *fa,FILE *fb)
{
    if (fa == NULL)
    {
        printf("Cannot open file \n");
        exit(0); 
    }
    char ca = getc(fa);
    while (ca != EOF)
    {
        if(ca ==' ')
        {
            putc(ca,fb);
            while(ca==' ')
                ca = getc(fa);
        }
        if (ca=='/')
        {
            char cb = getc(fa);
            if (cb == '/')
            {
                while(ca != '\n')
                    ca = getc(fa);
            }
            else if (cb == '*')
            {
                do
                {
                    while(ca != '*')
                        ca = getc(fa);
                    ca = getc(fa);
                } while (ca != '/');
            }
            else
            {
                putc(ca,fb);
                putc(cb,fb);
            }
        }
        else 
            putc(ca,fb);
        ca = getc(fa);
    }
}