#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>


typedef struct Process
{
    int id;
    int AT,BT,CT,TAT,WT,RT;
    int count;
}Process;

void sortByAT(Process *P,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(P[i].AT > P[i].AT)
            {
                Process temp = P[i];
                P[i] = P[j];
                P[j] = temp;
            }
            if(P[i].BT == P[j].BT)
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


void SRTF(Process *P,int n)
{
    int remaining_time[n];
    for(int i=0;i<n;i++)
    {
        P[i].count = 0;
        remaining_time[i] = P[i].BT;
    }
    int completed=0,t=0;
    int check=0;
    int minm = 10000;
    int shortest = 0;
    int firstTimeCPU = 0;
    while(completed != n)
    {
        for(int i=0;i<n;i++)
        {
            if((P[i].AT <= t) && (remaining_time[i] < minm) && (remaining_time[i] > 0))
            {
                if(P[i].count == 0)
                {
                    firstTimeCPU = t;
                    P[i].RT = firstTimeCPU - P[i].AT;
                    P[i].count = 1;
                }
                minm = remaining_time[i];
                shortest = i;
                check = 1;
            }
        }
        if(check == 0)
        {
            t++;
            continue;
        }
        remaining_time[shortest]--;
        minm = remaining_time[shortest];
        if(minm == 0)
        {
            minm = 10000;
        }
        if(remaining_time[shortest] == 0)
        {
            completed++;
            check = 0;
            P[shortest].CT = t+1;
            P[shortest].TAT = P[shortest].CT - P[shortest].AT;
            P[shortest].WT = P[shortest].TAT - P[shortest].BT;
            if(P[shortest].WT < 0)
                P[shortest].WT = 0;
        }
        t++;
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
}

void display(Process *P,int n)
{
    sortByPid(P,n);
    printf("\n\nALGORITHM OUTPUT:\n");
    printf("PID\tAT\tBT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",P[i].id,P[i].AT,P[i].BT,P[i].TAT,P[i].WT,P[i].RT);
    }
}


int main()
{
    int n;
    printf("enter no. of processes:");
    scanf("%d",&n);
    Process *P = (Process*)calloc(n,sizeof(Process));
    input(P,n);
    SRTF(P,n);
    display(P,n);
}