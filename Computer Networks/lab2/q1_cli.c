#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORTNO 4021
int main()
{
    int sockfd,n=1,result,pid_c;
    struct sockaddr_in address;
    int size;
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
    scanf("%d",&size);
    write(sockfd,&size,sizeof(size));
    int *arr = (int*)calloc(size,sizeof(int));
    printf("\nenter array:\t");
    for(int i=0;i<size;i++)
    {
        scanf("%d",&arr[i]);
    }
    write(sockfd,arr,size*sizeof(int));
    printf("sorted array sent back from server is:");
    n = read(sockfd,arr,size*sizeof(int));
    read(sockfd,&pid_c,sizeof(pid_c));
    for(int i=0;i<size;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\npid is:%d",pid_c);
    close(sockfd);
}