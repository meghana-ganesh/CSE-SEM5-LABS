#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORTNO 10200
int main()
{
    int sockfd,len,n=1,result;
    struct sockaddr_in address;
    char ch[256],buf[256],encrypt[256];
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("172.16.59.34");
    address.sin_port = htons(PORTNO);
    result = connect(sockfd,(struct sockaddr*)&address,sizeof(address));
    if(result==-1)
    {
        perror("\nCLIENT ERROR");
        exit(1);
    }
    printf("\nENTER STRING\t");
    gets(ch);
    ch[strlen(ch)]='\0';
    for(int i=0;i<strlen(ch);i++)
    {
        ch[i] = ch[i] + 4;
    }
    write(sockfd,ch,strlen(ch));
    printf("encrypted message:%s",ch);
    printf("\nDECRYPTED STRING SENT BACK FROM SERVER IS ..... ");
    while(n)
    {
        n=read(sockfd,buf,sizeof(buf));
        puts(buf);
    }
}
