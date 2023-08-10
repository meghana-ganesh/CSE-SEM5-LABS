#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORTNO 7002
int main()
{
    int len,result,sockfd,n=1;
    struct sockaddr_in address;
    char ch[256],buf[256];
    sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    address.sin_family=AF_LOCAL;
    address.sin_addr.s_addr=inet_addr("127.0.0.1");
    address.sin_port=htons(PORTNO);
    len = sizeof(address);
    result=connect(sockfd,(struct sockaddr *)&address,len);
    if(result==-1)
    {
        perror("\nCLIENT ERROR");
        exit(1);
    }
    printf("\nENTER STRING\t");
    gets(ch);
    ch[strlen(ch)]='\0';
    write(sockfd,ch,strlen(ch));
    printf("STRING SENT BACK FROM SERVER IS ..... ");
    while(n)
    {
        n=read(sockfd,buf,sizeof(buf));
        puts(buf);
    }
}