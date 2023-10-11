#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

typedef struct my_msg_st
{
    long int my_msg_type;
    int x;
}my_msg_st;

void main()
{
    my_msg_st input;
    int num;
    int msgid = msgget((key_t)1234,0666|IPC_CREAT);
    if(msgid == -1)
    {
        fprintf(stderr,"msgget failed!\n");
        exit(0);
    }
    printf("enter a number:");
    scanf("%d",&num);
    if(num < 0)
    {
        printf("invalid no.!enter only positive no.s!\n");
        exit(0);
    }
    input.x = num;
    input.my_msg_type = 1;
    int sent = msgsnd(msgid,(void*)&input,sizeof(int),0);
    if(sent == -1)
    {
        fprintf(stderr,"msgsnd failed!\n");
        exit(0);
    }
}
