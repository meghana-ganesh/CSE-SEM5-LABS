#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORTNO 7012
int main()
{
    int sockfd,n=1,result,num1,num2,res;
    char op;
    struct sockaddr_in address;
    sockfd = socket(AF_LOCAL,SOCK_STREAM,0);
    address.sin_family = AF_LOCAL;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);
    result=connect(sockfd,(struct sockaddr *)&address,sizeof(address));
    if(result == -1)
    {
        perror("\nCLIENT ERROR");
        exit(0);
    }
    printf("enter num1:");
    scanf("%d",&num1);
    write(sockfd,&num1,sizeof(num1));
    printf("\nenter num2:");
    scanf("%d",&num2);
    write(sockfd,&num2,sizeof(num2));
    printf("\nenter operator:");
    while (getchar() != '\n');
    scanf("%c",&op);
    write(sockfd,&op,sizeof(op));
    read(sockfd,&res,sizeof(res));
    printf("\ncalculated result from server is:%d",res);
    close(sockfd);
}