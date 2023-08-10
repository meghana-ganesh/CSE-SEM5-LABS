#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<stdio.h>
int main(int argc,char *argv[])
{
    int fd = open(argv[2],O_RDONLY);
    int count = 0,lncount = 1;
    int out;
    char c;
    char line[100];
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
            if(strstr(line,argv[1]))
            {
                // printf("%s\n",line);
                write(out,line,strlen(line)+1);
                printf("\n");
            }
            count = 0;
        }
    }
    if (count > 0) {
        line[count] = '\0';
        if (strstr(line, argv[1])) {
            printf("%s\n", line);
        }
    }
    printf("total no. of lines in the file:%d",lncount);
    close(fd);
    return 0;
}