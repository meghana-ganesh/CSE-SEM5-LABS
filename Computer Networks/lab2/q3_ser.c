#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>
#define PORTNO 7001
int main()
{
    int sockfd,newsockfd,n=1,clilen;
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
            int pid_c = getpid();
            char datetime[256] = {""};
            time_t t;
            time(&t);
            strcpy(datetime,ctime(&t));
            write(newsockfd,datetime,sizeof(datetime));
            write(newsockfd,&pid_c,sizeof(pid_c));
            close(newsockfd);
        }
        else
        {
            close(newsockfd);
        }
    }
}