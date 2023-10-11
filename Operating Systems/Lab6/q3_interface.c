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
    char text[2];
}shared_use_st;

void main()
{
    shared_use_st *shared_stuff;
    srand((unsigned int)getpid());
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
    shared_stuff->written_by_you = 0;
    //set the shared_stuff pointer to point to the 
    //same memory location as shared_memory but with the type shared_use_st.
    shared_stuff = (shared_use_st *)shared_memory;
}
