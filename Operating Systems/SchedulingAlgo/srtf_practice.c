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


void SRTF(Process *P,int n)
{
    int minm = 10000;
    int check = 0;
    int shortest = 0;
    int t = 0;
    int completed = 0;
    int remaining_time[n];
    int firstTimeCPU = 0;
    for(int i=0;i<n;i++)
    {
        P[i].count = 0;
        remaining_time[i] = P[i].BT;
    }

    while(completed != n)
    {
        for(int i=0;i<n;i++)
        {
            if((P[i].AT <= t) && (remaining_time[i] < minm) && remaining_time[i] > 0)
            {
                if(P[i].count == 0)
                {
                    firstTimeCPU = t;
                    P[i].RT = firstTimeCPU - P[i].AT;
                    P[i].count = 1;
                }
                check = 1;
                shortest = i;
                minm = remaining_time[i];
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
            minm  = 10000;
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
        printf("\nenter the AT,BT of Process %d:",i);
        scanf("%d %d",&P[i].AT,&P[i].BT);
        P[i].id = i;
    }
    sortByAT(P,n);
}


void display(Process *P,int n)
{
    sortByPid(P,n);
    printf("\nPID\tAT\tBT\tTAT\tWT\tRT");
    for(int i=0;i<n;i++)
    {
        printf("\n%d\t%d\t%d\t%d\t%d\t%d",P[i].id,P[i].AT,P[i].BT,P[i].TAT,P[i].WT,P[i].RT);
    }
}


int main()
{
    int n;
    printf("enter the no. of processes:");
    scanf("%d",&n);
    Process *P = (Process*)malloc(n*sizeof(Process));
    input(P,n);
    SRTF(P,n);
    display(P,n);
}