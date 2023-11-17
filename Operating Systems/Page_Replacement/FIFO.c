#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>


void FIFO(int arr[],int **frame,int n,int f)
{
    int *queue = (int*)malloc(100*sizeof(int));
    int front = 0,rear = 0;
    int hits = 0;
    int faults = 0;
    int *tempframe = (int*)malloc(f*sizeof(int));
    for(int i=0;i<f;i++)
    {
        tempframe[i] = -1;
    }
    for(int i=0;i<n;i++)
    {
        int flag = 0;
        int empty = 0;
        for(int j=0;j<f;j++)
        {
            if(tempframe[j] == arr[i])
            {
                flag = 1;
                hits++;
            }
        }
        if(flag == 0)
        {
            faults++;
            for(int j=0;j<f;j++)
            {
                if(tempframe[j] == -1)
                {
                    empty = 1;
                    tempframe[j] = arr[i];
                    queue[rear++] = arr[i];
                    break;
                }
            }
            if(empty == 0)
            {
                for(int j=0;j<f;j++)
                {
                    if(queue[front] == tempframe[j])
                    {
                        tempframe[j] = arr[i];
                        queue[rear++] = arr[i];
                        front++;
                        break;
                    }
                }
            }
        }
        for(int j=0;j<f;j++)
        {
            frame[i][j] = tempframe[j];
        }
        printf("\nframe for %d:",arr[i]);
        for(int j=0;j<f;j++)
        {
            printf("%d ",frame[i][j]);
        }
    }
    printf("\nPAGE HITS:%d,PAGE FAULTS:%d",hits,faults);
}




void input(int arr[],int n)
{
    printf("enter the reference string:");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
}

int main()
{
    int n,f;
    printf("enter the length of the reference string:");
    scanf("%d",&n);
    printf("enter the no. of frames:");
    scanf("%d",&f);
    int arr[n];
    int **frame = (int**)malloc(n*sizeof(int*));
    for(int i=0;i<n;i++)
    {
        frame[i] = (int*)malloc(f*sizeof(int));
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<f;j++)
        {
            frame[i][j] = -1;
        }
    }
    input(arr,n);
    FIFO(arr,frame,n,f);
}