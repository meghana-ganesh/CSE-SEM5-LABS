#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORTNO 7012
int calculate(int num1,int num2,char op)
{
    int res = 0;
    switch(op)
    {
        case '+':
            res = num1 + num2;
            break;
        case '-':
            res = num1 - num2;
            break;
        case '*':
            res = num1 * num2;
            break;
        case '/':
            res = num1 / num2;
            break;
        case '%':
            res = num1 % num2;
            break;
        default:
            break;
    }
    return res;
}
int main()
{
    int sockfd,newsockfd,n=1,clilen,num1,num2;
    char op;
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
            int res = 0;
            read(newsockfd,&num1,sizeof(num1));
            printf("\nnum1 from client:%d",num1);
            read(newsockfd,&num2,sizeof(num2));
            printf("\nnum2 from client:%d",num2);
            read(newsockfd,&op,sizeof(op));
            printf("\noperator from client is:%c",op);
            res = calculate(num1,num2,op);
            write(newsockfd,&res,sizeof(res));
            close(newsockfd);
            exit(0);
        }
        else
        {
            close(newsockfd);
        }
    }
}