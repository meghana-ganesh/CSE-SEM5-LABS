#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE PIPE_BUF
int main()
{
    int pipe_fd;
    int res;
    int open_mode = O_RDONLY;
    int bytes_read = 0;
    int arr[4];
    printf("Process %d opening FIFO O_RDONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);
    printf("Process %d result %d\n", getpid(), pipe_fd);
    if(pipe_fd != -1)
    {
        do 
        {
            res = read(pipe_fd,arr,sizeof(arr));
            bytes_read += res;
        }while (res > 0);
        close(pipe_fd);
    }
    else 
    {
        exit(EXIT_FAILURE);
    }
    printf("Process %d finished, %d bytes read\n", getpid(), bytes_read);
    printf("\nThe array is:");
    for(int i=0;i<4;i++)
    {
        printf("%d ",arr[i]);
    }
    exit(EXIT_SUCCESS);
}