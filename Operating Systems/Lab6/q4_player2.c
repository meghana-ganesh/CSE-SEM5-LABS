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
    int mat[9];
}shared_use_st;

void main()
{
    shared_use_st *shared_stuff;
    void *shared_memory = (void*)0;
    int shmid = shmget((key_t)1236,sizeof(shared_use_st),0666|IPC_CREAT);
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
    printf("memory attached at:%X",(int)shared_memory);
    shared_stuff = (shared_use_st *)shared_memory;
}