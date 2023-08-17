#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORTNO 5006
int main()
{
    int sockfd;
    char buf[256];
    struct sockaddr_in seraddr,cliaddr;
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("10.75.5.63");
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
    int clilen = sizeof(cliaddr);
    recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&cliaddr,&clilen);
    printf("the message sent by client is:\n");
    printf("%s",buf);
    sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&cliaddr,clilen);
    return 0;
}