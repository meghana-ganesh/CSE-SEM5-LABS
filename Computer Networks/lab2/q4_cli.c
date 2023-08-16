#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORTNO 6007
int main()
{
    int sockfd,n=1,result;
    char str[256] = {""};
    struct sockaddr_in address;
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
    printf("enter a sentence:");
    gets(str);
    // scanf("%[^\n]s",str);
    str[strlen(str)] = '\0';
    write(sockfd,str,strlen(str));
    close(sockfd);
    return 0;
}