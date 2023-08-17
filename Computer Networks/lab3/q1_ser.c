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
    int sockfd;
    char buf[256];
    struct sockaddr_in seraddr,cliaddr;
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("10.75.5.63");
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
    int clilen = sizeof(cliaddr);

    int received_rows = 0;
    int mat[ROWS][COLS];
    while (received_rows < ROWS) 
    {
        recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&cliaddr, &clilen);
        sscanf(buf,"%d %d %d",&mat[received_rows][0],&mat[received_rows][1],&mat[received_rows][2]);
        received_rows++;
    }
    printf("Received matrix:\n");
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; j++) 
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    return 0;
}