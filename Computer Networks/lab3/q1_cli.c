#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORTNO 5008
#define ROWS 3
#define COLS 3
int main()
{
    int sockfd,len;
    struct sockaddr_in address;
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("10.75.5.63");
    address.sin_port = htons(PORTNO);
    len = sizeof(address);

    int mat[ROWS][COLS] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    for (int i = 0; i < ROWS; i++) 
    {
        char buf[256];
        snprintf(buf, sizeof(buf), "%d %d %d", mat[i][0], mat[i][1], mat[i][2]);
        len = sizeof(address);
        sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&address, len);
    }
    printf("Sent matrix rows to server.\n");
    return 0;
}
