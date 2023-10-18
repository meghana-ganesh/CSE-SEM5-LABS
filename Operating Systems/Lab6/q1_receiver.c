#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<math.h>

typedef struct my_msg_st
{
    long int my_msg_type;
    int x;
}my_msg_st;

int check_palindrome(int n)
{
    int revnum = 0;
    int num = n;
    while(n > 0)
    {
        int dig = n % 10;
        n = n / 10;
        revnum = revnum*10 + dig;
    }
    if(revnum == num)
        return 1;
    return 0;
}
//1001
//

void main()
{
    my_msg_st input;
    int msgid = msgget((key_t)1234,0666|IPC_CREAT);
    if(msgid == -1)
    {
        fprintf(stderr,"msgget failed!\n");
        exit(0);
    }
    int msg_to_receive = 1;
    int rcvd = msgrcv(msgid,(void*)&input,sizeof(int),msg_to_receive,0);
    if(rcvd == -1)
    {
        fprintf(stderr,"msgrcv failed!\n");
        exit(0);
    }
    printf("number received is:%d\n",input.x);
    if(check_palindrome(input.x))
        printf("palindrome!");
    else
        printf("not a palindrome!");
    int cntl = msgctl(msgid, IPC_RMID, 0);
    if (cntl == -1) 
	{
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
		exit(0);
	}
    exit(0);
}