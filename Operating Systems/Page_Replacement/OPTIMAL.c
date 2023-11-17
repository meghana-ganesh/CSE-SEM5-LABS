#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>


void optimal(int arr[],int **frame,int n,int f)
{
    int *tempframe = (int*)malloc(f*sizeof(int));
    for(int i=0;i<f;i++)
    {
        tempframe[i] = -1;
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
                    break;
                }
            }
            if(empty == 0)
            {
                int farthest = -10000;
                int pos = 0;
                int ind = -1;
                for(int j=0;j<f;j++)
                {
                    int found = 0;
                    for(int x=i+1;x<n;x++)
                    {
                        if(tempframe[j] == arr[x])
                        {
                            found = 1;
                            pos = x;
                            break;
                        }
                    }
                    if(found == 0)
                    {
                        farthest = 10000;
                        ind = j;
                    }
                    else
                    {
                        if(pos > farthest)
                        {
                            farthest = pos;
                            ind = j;
                        }
                    }
                }
                for(int j=0;j<f;j++)
                {
                    // printf("\nMIN%d",min);
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
    printf("\nHITS:%d,PAGE FAULTS:%d",hits,faults);
}

int main()
{
    int n,f;
    printf("enter the length of reference string:");
    scanf("%d",&n);
    printf("ente the no. of frames:");
    scanf("%d",&f);
    int arr[n];
    printf("enter the reference string:");
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
    optimal(arr,frame,n,f);
}