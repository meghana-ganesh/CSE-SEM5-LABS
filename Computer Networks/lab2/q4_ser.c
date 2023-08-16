#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORTNO 6007
void removeduplicates(char str[],char res[],char words[][256])
{
    
}
int main()
{
    int sockfd,n=1,result,newsockfd,clilen;
    char buf[256] = {""};
    char res[256] = {""};
    char words[256][256] = {""};
    struct sockaddr_in seraddress,cliaddr;
    sockfd = socket(AF_LOCAL,SOCK_STREAM,0);
    seraddress.sin_family = AF_LOCAL;
    seraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddress.sin_port = htons(PORTNO);
    bind(sockfd,(struct sockaddr *)&seraddress,sizeof(seraddress));
    listen(sockfd,5);
    while(1)
    {
        clilen = sizeof(clilen);
        newsockfd = accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
        if(fork() == 0)
        {
            read(newsockfd,buf,sizeof(buf));
            printf("\nsentence sent by client is:%s",buf);
            removeduplicates(buf,res,words);
            close(newsockfd);
            exit(0);
        }
        else
        {
            close(newsockfd);
        }
    }
    return 0;
}