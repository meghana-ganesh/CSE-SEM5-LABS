#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


void LRU(int arr[],int **frame,int n,int f)
{
    int *stack = (int*)malloc(100*sizeof(int));
    int *tempframe = (int*)malloc(f*sizeof(int));
    for(int i=0;i<f;i++)
    {
        tempframe[i] = -1;
    }
    int hits = 0;
    int faults = 0;
    int k = 0;
    for(int i=0;i<n;i++)
    {
        int flag = 0;
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
            int empty = 0;
            faults++;
            for(int j=0;j<f;j++)
            {
                if(tempframe[j] == -1)
                {
                    empty = 1;
                    tempframe[j] = arr[i];
                    break;
                }
            }
            if(empty == 0)
            {
                int lru_pos = 0;
                int least = 10000;
                int ind = -1;
                for(int j=0;j<f;j++)
                {
                    for(int x=i-1;x>=0;x--)
                    {
                        if(arr[x] == tempframe[j])
                        {
                            lru_pos = x;
                            break;
                        }
                    }
                    if(lru_pos < least)
                    {
                        least = lru_pos;
                        ind = j;
                    }
                }
                for(int j=0;j<f;j++)
                {
                    if(j == ind)
                    {
                        tempframe[j] = arr[i];
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
    printf("enter the no. of processes:");
    scanf("%d",&n);
    printf("\nenter the no. of frames:");
    scanf("%d",&f);
    int arr[n];
    printf("\nenter the reference string:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    int **frame = (int**)malloc(n*sizeof(int*));
    for(int i=0;i<n;i++)
    {
        frame[i] = (int*)malloc(f*sizeof(int));
        for(int j=0;j<f;j++)
        {
            frame[i][j] = -1;
        }
    }
    LRU(arr,frame,n,f);
}