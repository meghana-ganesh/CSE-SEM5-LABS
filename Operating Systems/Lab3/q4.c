#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <sys/wait.h>
int main()
{
    pid_t pid;
    char *message;
    int n;
    printf("fork program starting\n");
    pid = fork();
    switch(pid)
    {
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            message = "This is the child";
            n = 3;
            break;
        default:
            message = "This is the parent";
            n = 5;
            break;
    }
    for(; n > 0; n--) 
    {
        puts(message);
        sleep(1);
    }
}