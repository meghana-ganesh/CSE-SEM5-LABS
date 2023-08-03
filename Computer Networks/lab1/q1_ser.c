#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORTNO 10200
int main()
{
    int sockfd,newsockfd,portno,clilen,n=1;
    struct sockaddr_in seraddr,cliaddr;
    int i,value;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("172.16.59.34");
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd,(struct sockaddr*)&seraddr,sizeof(seraddr));
    listen(sockfd,5);
    while(1)
    {
        char buf[256];
        printf("server waiting");
        //accept a connection
        clilen = sizeof(clilen);
        newsockfd = accept(sockfd,(struct sockaddr*)&cliaddr,&clilen);
        //read and write to client
        n = read(newsockfd,buf,sizeof(buf));
        printf("\n encrypted message from client %s \n",buf);
        for(int i=0;i<strlen(buf);i++)
        {
            buf[i] = buf[i] - 4;
        }
        printf("\ndecrypted message from client %s\n",buf);
        n = write(newsockfd,buf,sizeof(buf));
    }
}