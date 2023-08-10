#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
    char c;
    int fd = open(argv[1],O_RDONLY);
    if(fd == -1)
    {
        printf("file not opened");
    }
    int out;
    int lncount = 1;
    int count = 0;
    char line[256];
    while(read(fd,&c,1) > 0)
    {
        if(c != '\n')
        {
            line[count++] = c;
        }
        else
        {
            lncount++;
            line[count] = '\0';
            printf("%s\n",line);
            if((lncount % 3) == 0)
            {
                
                char x;
                printf("more..(press enter to continue)");
                fflush(stdin);
                scanf("%c",&x);
                printf("\n");
            }
            count = 0;
        }
    }
    printf("\nmore....");
}