#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"
#define MAX_ITEMS 5

int main()
{
    int pipe_fd;
    int res;
    int open_mode = O_WRONLY;
    
    if (access(FIFO_NAME, F_OK) == -1)
    {
        res = mkfifo(FIFO_NAME, 0777);
        if (res != 0) {
            fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
            exit(EXIT_FAILURE);
        }
    }
    
    printf("Producer opening FIFO O_WRONLY\n");
    pipe_fd = open(FIFO_NAME, open_mode);
    printf("Producer result %d\n", pipe_fd);
    if (pipe_fd != -1) 
    {
        while (1) 
        {
            res = write(pipe_fd, "add", sizeof("add"));
            if (res == -1) 
            {
                fprintf(stderr, "Write error on pipe\n");
                exit(EXIT_FAILURE);
            }
            printf("Producer added one item\n");
            usleep(500000);  // Sleep for 500 milliseconds
        }
        close(pipe_fd);
    } 
    else 
    {
        exit(EXIT_FAILURE);
    }
    printf("Producer finished\n");
    exit(EXIT_SUCCESS);
}
