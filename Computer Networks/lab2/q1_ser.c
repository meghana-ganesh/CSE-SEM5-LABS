#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORTNO 4030
void sortArray(int arr[], int size) 
{
    for (int i=0;i<size-1;i++) 
    {
        for (int j=0;j<size-i-1;j++) 
        {
            if (arr[j]>arr[j + 1]) 
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
        int arr[256];
        int sortedarr[256];
        clilen = sizeof(clilen);
        newsockfd = accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
        if(fork() == 0)
        {
            read(newsockfd,arr,sizeof(arr));
            int m = sizeof(arr)/sizeof(int);
            printf(" \nMessage from Client:");
            for(int i=0;i<m;i++)
            {
                printf("%d ",arr[i]);
            }
            sortArray(arr,m);
            write(newsockfd,sortedarr,sizeof(sortedarr));
            close(newsockfd);
            exit(0);
        }
        else
        {
            close(newsockfd);
        }
    }
}
