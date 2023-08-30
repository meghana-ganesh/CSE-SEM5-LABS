#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<string.h>

#define FIFO_NAME "/tmp/my_fifo"
#define MAX_ITEMS 5

int main()
{
    int pipe_fd;
    int res;
    int open_mode = O_RDONLY;
    int shelf_count = 0;
    
    printf("Consumer opening FIFO O_RDONLY\n");
    pipe_fd = open(FIFO_NAME, open_mode);
    printf("Consumer result %d\n", pipe_fd);
    
    if (pipe_fd != -1) 
    {
        while (1) 
        {
            char action[4];
            res = read(pipe_fd, action, sizeof(action));
            if(strcmp(action,"add") == 0)
            {
                printf("yes");
                shelf_count++;
            }
            if (res == -1) 
            {
                fprintf(stderr, "Read error on pipe\n");
                exit(EXIT_FAILURE);
            }
            if (shelf_count > 0) 
            {
                shelf_count--;
                printf("Consumer removed one item. Shelf count: %d\n", shelf_count);
            } 
            else 
            {
                printf("Consumer found no items on the shelf.\n");
            }
            usleep(300000);  // Sleep for 300 milliseconds
        }
        close(pipe_fd);
    } 
    else 
    {
        exit(EXIT_FAILURE);
    }
    
    printf("Consumer finished\n");
    exit(EXIT_SUCCESS);
}
