#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

typedef struct Process
{
    int id;
    int AT,BT,CT,TAT,WT,RT;
}Process;


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



void FCFS(Process *P,int n)
{
    int time = 0;
    for(int i=0;i<n;i++)
    {
        if(i == 0)
        {
            time = P[i].AT;
        }
        P[i].CT = time + P[i].BT;
        printf("Process %d completed at time %d.\n",P[i].id,P[i].CT);
        P[i].TAT = P[i].CT - P[i].AT;
        P[i].WT = P[i].TAT - P[i].BT;
        P[i].RT = time - P[i].AT;
        time = P[i].CT;
        sleep(1);
    }
}

void input(Process *P,int n)
{
    for(int i=0;i<n;i++)
    {
        printf("enter the AT,BT for process %d:",i);
        scanf("%d %d",&P[i].AT,&P[i].BT);
        P[i].id = i;
    }
    sortByAT(P,n);
}


void display(Process *P,int n)
{
    sortByPid(P,n);
    printf("\nPID\tAT\tBT\tTAT\tWT\tRT\n\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",P[i].id,P[i].AT,P[i].BT,P[i].TAT,P[i].WT,P[i].RT);
    }
}



int main()
{
    int n;
    printf("enter the no. of processes:");
    scanf("%d",&n);
    Process *P = (Process*)calloc(n,sizeof(Process));
    input(P,n);
    FCFS(P,n);
    display(P,n);
}