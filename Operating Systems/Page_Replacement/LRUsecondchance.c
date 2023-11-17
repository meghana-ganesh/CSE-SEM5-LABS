#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>


int front = 0,rear = 0;

void LRUSecondChance(int arr[],int **frame,int n,int f)
{
    int *tempframe = (int*)calloc(f,sizeof(int));
    int *clock = (int*)calloc(f,sizeof(int));
    int *queue = (int*)malloc(100*sizeof(int));
    for(int i=0;i<f;i++)
    {
        tempframe[i] = -1;
        clock[i] = 0;
    }
    int hits = 0;
    int faults = 0;
    for(int i=0;i<n;i++)
    {
    int flag = 0;
            int empty = 0;

        for(int j=0;j<f;j++)
        {
            if(tempframe[j] == arr[i])
            {
                hits++;
                clock[j] = 1;
                flag = 1;
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
                    clock[j] = 0;
                    queue[rear++] = arr[i];
                    tempframe[j] = arr[i];
                    break;
                }
            }
            if(empty == 0)
            {
                for(int j=0;j<f;j++)
                {
                    if(tempframe[j] == queue[front])
                    {
                        if(clock[j] == 1)
                        {
                            clock[j] = 0;
                            int x = front + 1;
                            for(int j=0;j<f;j++)
                            {
                                if(tempframe[j] == queue[x])
                                {
                                    tempframe[j] = arr[i];
                                    queue[rear++] = arr[i];
                                    queue[x] = queue[front];
                                    front++;
                                    break;
                                }
                            }
                            break;
                        }
                        else
                        {
                            tempframe[j] = arr[i];
                            front++;
                            queue[rear++] = arr[i];
                            break;
                        }
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
    
}


int main()
{
    int n,f;
    printf("enter the length of reference string:");
    scanf("%d",&n);

    printf("\nenter the no. of frames:");
    scanf("%d",&f);

    int arr[n];
    printf("\nenter the reference string:");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }

    int **frame = (int**)calloc(n,sizeof(int*));
    for(int i=0;i<n;i++)
    {
        frame[i] = (int*)calloc(f,sizeof(int));
        for(int j=0;j<f;j++)
        {
            frame[i][j] = -1;
        }
    }
    LRUSecondChance(arr,frame,n,f);
}