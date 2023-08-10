#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
    int fd = open(argv[1],O_RDONLY);
    if(fd == -1)
    {
        printf("couldnt open input file");
    }
    int fd1 = open(argv[2],O_WRONLY);
    if(fd1 == -1)
    {
        printf("couldnt open output file");
    }
    char c;
    while(read(fd,&c,1)>0)
    {
        write(fd1,&c,1);
    }
    printf("\ncopy done.");
}