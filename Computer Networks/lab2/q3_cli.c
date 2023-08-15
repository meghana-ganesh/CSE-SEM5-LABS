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
    int sockfd,n=1,clilen,result,pid_c;
    struct sockaddr_in address,cliaddr;
    char datetime[256] = {""};
    sockfd = socket(AF_LOCAL,SOCK_STREAM,0);
    address.sin_family = AF_LOCAL;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);
    result = connect(sockfd,(struct sockaddr *)&address,sizeof(address));
    if(result == -1)
    {
        perror("\nCLIENT ERROR");
        exit(0);
    }
    read(sockfd,datetime,sizeof(datetime));
    printf("\nthe date and time sent from the server is:%s",datetime);
    read(sockfd,&pid_c,sizeof(pid_c));
    printf("\nthe process id is:%d",pid_c);
    close(sockfd);
    return 0;
}