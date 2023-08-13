#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORTNO 4021
void sortArray(int *arr, int size) 
{
    for (int i=0;i<size;i++) 
    {
        for (int j=0;j<size-i-1;j++) 
        {
            if (arr[j] >arr[j + 1]) 
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
int main()
{
    int sockfd,newsockfd,portno,clilen,n=1,x;
    struct sockaddr_in seraddr,cliaddr;

    sockfd = socket(AF_LOCAL,SOCK_STREAM,0);
    seraddr.sin_family = AF_LOCAL;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);

    bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
    listen(sockfd,5);

    while(1)
    {
        clilen = sizeof(clilen);
        newsockfd = accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
        if(fork() == 0)
        {
            int size,pid_c;
            pid_c = getpid();
            n = read(newsockfd,&size,sizeof(size));
            int *arr = (int*)calloc(size,sizeof(int));
            n = read(newsockfd,arr,size*sizeof(int));
            printf(" \nArray from Client:");
            for(int i=0;i<size;i++)
            {
                printf("%d ",arr[i]);
            }
            sortArray(arr,size);
            write(newsockfd,arr,size*sizeof(int));
            write(newsockfd,&pid_c,sizeof(pid_c));
            close(newsockfd);
            exit(0);
        }
        else
        {
            close(newsockfd);
        }
    }
}
