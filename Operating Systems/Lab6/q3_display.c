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
    shared_use_st *shared_stuff;
    int running = 1;
    void *shared_memory = (void*)0;
    int shmid;
    // srand((unsigned int)getpid());
    shmid = shmget((key_t)1234,sizeof(shared_use_st),0666|IPC_CREAT);
    if(shmid == -1)
    {
        fprintf(stderr,"shmget failed!");
        exit(0);
    }
    shared_memory = shmat(shmid,(void*)0,0);
    if(shared_memory == (void*)-1)
    {
        fprintf(stderr,"shmat failed!");
        exit(0);
    }
    printf("Memory attached at %X\n",(int)shared_memory);
    shared_stuff = (shared_use_st*)shared_memory;
    shared_stuff->written_by_you = 0;
    while(running)
    {
        if(shared_stuff->written_by_you)
        {
            printf("You wrote:%s",shared_stuff->text);
            memset(shared_stuff->text, 0, sizeof(shared_stuff->text));
            shared_stuff->written_by_you = 0;
            if(strncmp(shared_stuff->text,"end",3) == 0)
            {
                running = 0;
            }
        }
    }
    if(shmdt(shared_memory) == -1)
    {
        fprintf(stderr,"shmdt failed!");
        exit(0);
    }
    if(shmctl(shmid,IPC_RMID,0) == 0)
    {
        fprintf(stderr,"shmctl failed!");
        exit(0);
    }
    exit(1);
}