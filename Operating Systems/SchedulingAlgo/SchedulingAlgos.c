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

//TAT = CT-AT
//WT = TAT-BT
//RT = 1st time CPU - AT

void execute(Process *P,int n,int i,int *time)
{
    if(i == 0)
    {
        *time = P[i].AT;
        P[i].CT = *time + P[i].BT;
        printf("Process %d completed at time %d.\n",P[i].id,P[i].CT);
        P[i].TAT = P[i].CT - P[i].AT;
        P[i].WT = P[i].TAT - P[i].BT;
        P[i].RT = *time - P[i].AT;
        *time = P[i].CT;
    }
    else
    {
        P[i].CT = *time + P[i].BT;
        printf("Process %d completed at time %d.\n",P[i].id,P[i].CT);
        P[i].TAT = P[i].CT - P[i].AT;
        P[i].WT = P[i].TAT - P[i].BT;
        P[i].RT = *time - P[i].AT;
        *time = P[i].CT;
    }
}

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
            else if(P[i].AT == P[j].AT)
            {
                if(P[i].id > P[j].id)
                {
                    Process temp = P[i];
                    P[i] = P[j];
                    P[j] = P[i];
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
        execute(P,n,i,&time);
    }
}

void sortByATandSJF(Process *P,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(P[i].AT == P[i].AT)
            {
                if(P[i].BT > P[j].BT)
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
}


void SJF(Process *P,int n)
{
    sortByATandSJF(P,n);
    int time = 0;
    for(int i=0;i<n;i++)
    {
        execute(P,n,i,&time);
    }
}

void sortByBT(Process *P,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(P[i].BT > P[j].BT)
            {
                Process temp = P[i];
                P[i] = P[j];
                P[j] = temp;
            }
            else if(P[i].BT == P[j].BT)
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


void SRTF(Process *P,int n)
{
    int remaining_time[n];
    for(int i=0;i<n;i++)
    {
        P[i].count = 0;
        remaining_time[i] = P[i].BT;
    }

    int complete = 0,t = 0,firstTimeCPU=0;
    int minm = 10000,shortest = 0;
    int check = 0;

    while(complete != n)
    {
        for(int j=0;j<n;j++)
        {
            if((P[j].AT <= t) && (remaining_time[j] < minm) 
            && (remaining_time[j] > 0))
            {
                if(P[j].count == 0)
                {
                    firstTimeCPU = t;
                    P[j].RT = firstTimeCPU - P[j].AT;
                    P[j].count = 1;
                }
                minm = remaining_time[j];
                shortest = j;
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
            complete++;
            check = 0;
            P[shortest].CT = t + 1;
            P[shortest].TAT = P[shortest].CT - P[shortest].AT;
            P[shortest].WT = P[shortest].TAT - P[shortest].BT;
            if(P[shortest].WT < 0)
                P[shortest].WT = 0;
        }
        t++;
    }
}



void displayTable(Process *P,int n)
{
    sortByPid(P,n);
    printf("\n\nALGORITHM OUTPUT:\n");
    printf("PID\tAT\tBT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",P[i].id,P[i].AT,P[i].BT,P[i].TAT,P[i].WT,P[i].RT);
    }
}

void input(Process *P,int n)
{
    for(int i=0;i<n;i++)
    {
        printf("\nenter AT,BT for process %d:",i);
        scanf("%d %d",&P[i].AT,&P[i].BT);
        P[i].id = i;
    }
    printf("\n");
    for(int i=0;i<n;i++)
    {
        printf("PID:%d,AT:%d,BT:%d\n",P[i].id,P[i].AT,P[i].BT);
    }
    sortByAT(P,n);
}

int main()
{
    int n;
    printf("enter no. of processes:");
    scanf("%d",&n);
    Process *P = (Process*)calloc(n,sizeof(Process));
    input(P,n);
    // FCFS(P,n);
    // displayTable(P,n);
    // SJF(P,n);
    // displayTable(P,n);
    SRTF(P,n);
    displayTable(P,n);

}