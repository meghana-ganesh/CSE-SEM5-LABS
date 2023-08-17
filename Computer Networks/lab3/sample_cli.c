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
    int sockfd,len;
    struct sockaddr_in address;
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("10.75.5.63");
    address.sin_port = htons(PORTNO);
    char buf[256],buf1[256];
    printf("enter buf:");
    scanf("%[^\n]s",buf);
    len = sizeof(address);
    sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&address,len);
    printf("the server echo is\n");
    recvfrom(sockfd,buf1,sizeof(buf1),0,(struct sockaddr *)&address,&len);
    printf("%s",buf1);
    return 0;
}
