#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORTNO 6800
int main()
{
    int sockfd,n=1,result;
    struct sockaddr_in address;
    char buf[256],ch[256];
    sockfd = socket(AF_LOCAL,SOCK_STREAM,0);
    address.sin_family = AF_LOCAL;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);
    result = connect(sockfd,(struct sockaddr*)&address,sizeof(address));
    if(result == -1)
    {
        perror("\nCLIENT ERROR");
        exit(1);
    }
    while(strcmp(ch,"stop\n") != 0)
    {
        printf("\n ENTER STRING : ");
        gets(ch);
        ch[strlen(ch)] = '\0';
        write(sockfd,ch,strlen(ch));
        printf("STRING SENT BACK FROM SERVER IS ..... ");
        // while(n)
        // {
            read(sockfd,buf,sizeof(buf));
            puts(buf);
        // }
    }
}