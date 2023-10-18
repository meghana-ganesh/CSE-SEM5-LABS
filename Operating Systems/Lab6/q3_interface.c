#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

typedef struct shared_use_st
{
    int written_by_you;
    char text[256];
}shared_use_st;

void main()
{
    char buf[256];
    shared_use_st *shared_stuff;
    int running = 1;
    int shmid = shmget((key_t)1234,sizeof(shared_use_st),0666|IPC_CREAT);
    if (shmid == -1)
    {
        fprintf(stderr, "shmget failed\n");
        exit(0);
    }
    void *shared_memory = (void *)0;
    shared_memory = shmat(shmid,(void*)0,0);
    if (shared_memory == (void *)-1)
    {
        fprintf(stderr, "shmat failed\n");
        exit(0);
    }
    printf("Memory attached at %X\n", (int)shared_memory);
    //set the shared_stuff pointer to point to the 
    //same memory location as shared_memory but with the type shared_use_st.
    shared_stuff = (shared_use_st *)shared_memory;
    while(running)
    {
        while(shared_stuff->written_by_you == 1)
        {
            sleep(1);
            printf("waiting for client");
        }
        printf("\nEnter some text:");
        fgets(buf,sizeof(buf),stdin);
        memset(shared_stuff->text, 0, sizeof(shared_stuff->text));
        strncpy(shared_stuff->text,buf,strlen(buf));
        shared_stuff->written_by_you = 1;
        if(strncmp(buf,"end",3) == 0)
        {
            running = 0;
        }
    }
    if (shmdt(shared_memory) == -1) 
    {
        fprintf(stderr, "shmdt failed\n");
        exit(0);
    }
    exit(1);
}
