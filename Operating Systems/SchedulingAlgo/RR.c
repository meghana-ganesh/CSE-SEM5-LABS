#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

typedef struct Process
{
    int id;
    int AT,BT,CT,TAT,WT,RT;
    int count;
}Process;


int tq = 2;
int t = 0;
int firstTimeCPU = 0;
int count = 0;
int rr_count = 0;
int front = 0,rear = 0;


void sortByAT(Process *P,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(P[i].AT > P[j].AT)
            {
                Process temp = P[i];
                P[i] = P[j];
                P[j] = temp;
            }
            if(P[i].AT == P[j].AT)
            {
                if(P[i].id > P[j].id)
                {
                    Process temp = P[i];
                    P[i] = P[j];
                    P[j] = temp;
                }
            }
        }
    }
}


void sortByPid(Process *P,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(P[i].id > P[j].id)
            {
                Process temp = P[i];
                P[i] = P[j];
                P[j] = temp;
            }
        }
    }
}


void RR(Process *P,int n,int *remaining_time)
{
    int *queue = (int*)malloc(n*sizeof(int));
    int i;
    for(int i=0;i<100;i++)
    {
        queue[i] = -1;
    }
    int completed = 0;
    int toBeInserted = 0;
    int processToExecute = -10;
    while(completed != n)
    {
        for(i=toBeInserted;i<n && P[i].AT <= t;i++)
        {
            queue[rear++] = i;
        }
        if(processToExecute != -10 && remaining_time[processToExecute] > 0)
        {
            queue[rear++] = processToExecute;
        }
        toBeInserted = i;
        if(queue[front] == -1) //Check if queue is empty
        {
            t=P[toBeInserted].AT;
        }
        else
        {
            processToExecute = queue[front];
            queue[front] = -1;
            front++;
            if(remaining_time[processToExecute] > tq)
            {
                t+=tq;
                remaining_time[processToExecute]-=tq;
            }
            else
            {
                t+=remaining_time[processToExecute];
                P[processToExecute].CT=t;
                remaining_time[processToExecute]=0;
                P[processToExecute].TAT = P[processToExecute].CT - P[processToExecute].AT;
                P[processToExecute].WT=P[processToExecute].TAT-P[processToExecute].BT;
                completed++;
            }
        }
    }
}



void display(Process *P,int n)
{
    sortByPid(P,n);
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT");
    for(int i=0;i<n;i++)
    {
        printf("\n%d\t%d\t%d\t%d\t%d\t%d",P[i].id,P[i].AT,P[i].BT,P[i].CT,P[i].TAT,P[i].WT);
    }
}


void input(Process *P,int n)
{
    for(int i=0;i<n;i++)
    {
        printf("\nenter AT,BT of process %d:",i);
        scanf("%d %d",&P[i].AT,&P[i].BT);
        P[i].id = i;
    }
    sortByAT(P,n);
    for(int i=0;i<n;i++)
    {
        printf("\nAT:%d,BT:%d\n",P[i].AT,P[i].BT);
    }
}


int main()
{
    int n;
    printf("enter the no. of processes:");
    scanf("%d",&n);
    Process *P = (Process*)malloc(n*sizeof(Process));
    input(P,n);
    int *remaining_time = (int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++)
    {
        remaining_time[i] = P[i].BT;
    }
    RR(P,n,remaining_time);
    display(P,n);
}