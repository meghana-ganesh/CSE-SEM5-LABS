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
    if(pid == -1)
        printf("\nERROR child not created");
    else if (pid == 0) 
    {
        printf("\n I'm the child!");
        exit(0);
    }
    else
    {
        wait(&status);
        printf("\n I'm the parent!");
        printf("\n Child returned: %d\n", status);
    }
    return 0;
}
