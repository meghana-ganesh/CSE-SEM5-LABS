#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>
int main (int argc, char *argv[])
{
    struct stat sb;
    int ret;
    if (argc < 2) 
    {
        fprintf (stderr, "usage: %s <file>\n", argv[0]);
        return 1;
    }
    char *newpath = "/home/student/210905160/OS_Lab/Lab4/link/file.txt";
    printf("newpath:%s",newpath);
    // char *oldpath = "/home/student/210905160/OS_Lab/Lab4/file1.txt";
    if(symlink(argv[1],newpath)) 
    {
        perror("\nsymbolic link not created.");
        exit(1);
    }
    printf("\nsymbolic link created");
    int x;
    printf("\ndo you want to unlink?(1/0):");
    scanf("%d",&x);
    if(x == 1)
    {
        if(unlink(newpath))
        {
            perror("\nnot able to unlink.");
        }
        printf("\nunlinked.");
    }
    return 0;
}