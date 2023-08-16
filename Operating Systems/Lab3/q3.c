#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <sys/wait.h>
int main()
{
    int status;
    pid_t pid;
    pid = fork();
    if (pid == -1) 
    {
        printf("\nERROR child not created");
        exit(-1);
    }
    else if (pid == 0) 
    {
        printf("\nIn the child:");
        printf("\npid of the child:%d",getpid());
        printf("\npid of the parent is:%d",getppid());
        exit(1);
    }
    else
    { 
        wait(&status);
        printf("\nIn the parent:");
        printf("\npid of the child:%d",pid);
        printf("\npid of the parent is:%d",getpid());
        exit(0);
    }
}