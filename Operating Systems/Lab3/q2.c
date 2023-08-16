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
    /* fork another process */
    pid = fork();
    if (pid == -1) 
    {
        printf("\nERROR child not created");
        exit(-1);
    }
    else if (pid == 0) 
    {
        execl("/home/student/210905160/OS_Lab/Lab3/q1", "q1", NULL);
    }
    else 
    { 
        wait (NULL);
        printf ("Child Complete");
        exit(0);
    }
}