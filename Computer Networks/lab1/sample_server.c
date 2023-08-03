#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORTNO 10200
int main()
{
    int sockfd,newsockfd,portno,clilen,n=1;
    struct sockaddr_in seraddr,cliaddr;
    int i,value;
    //creating a socket for the server
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    //naming the socket
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("172.16.59.34");
    seraddr.sin_port = htons(PORTNO);
    //binding the socket to the server
    bind(sockfd,(struct sockaddr*)&seraddr,sizeof(seraddr));
    //create a connection queue and wait for clients
    listen(sockfd,5);//5 is queue limit
    while(1)
    {
        char buf[256];
        printf("server waiting");
        //accept a connection
        clilen = sizeof(clilen);
        newsockfd = accept(sockfd,(struct sockaddr*)&cliaddr,&clilen);
        //read and write to client
        n = read(newsockfd,buf,sizeof(buf));
        printf("\nmessage from client %s\n",buf);
        n = write(newsockfd,buf,sizeof(buf));
    }
    
}