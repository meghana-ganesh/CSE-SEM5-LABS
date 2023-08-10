#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORTNO 4030
int main()
{
    int sockfd,n=1,result;
    struct sockaddr_in address;
    int m;
    int sortedarr[256];
    sockfd = socket(AF_LOCAL,SOCK_STREAM,0);
    address.sin_family = AF_LOCAL;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);
    result=connect(sockfd,(struct sockaddr *)&address,sizeof(address));
    if(result==-1)
    {
        perror("\nCLIENT ERROR");
        exit(1);
    }
    printf("\nenter size of array:");
    scanf("%d",&m);
    int arr[m];
    printf("\nenter array:\t");
    for(int i=0;i<m;i++)
    {
        scanf("%d",&arr[i]);
    }
    write(sockfd,arr,sizeof(arr));
    printf("array sent back from server is:");
    read(sockfd,sortedarr,sizeof(sortedarr));
    for(int i=0;i<sizeof(sortedarr);i++)
    {
        printf("%d ",sortedarr[i]);
    }
    close(sockfd);
}