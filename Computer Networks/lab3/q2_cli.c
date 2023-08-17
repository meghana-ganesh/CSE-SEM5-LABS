#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
 
#define SERVER_IP "172.217.168.46"  // Google IP address
#define SERVER_PORT 80
 
int main() {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
 
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);
 
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }
 
    // char request[] = "GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n";
    char request[] = "GET /index.html HTTP/1.1\r\nHost: www.stackoverflow.com\r\n\r\n";
    if (send(client_socket, request, strlen(request), 0) == -1) 
    {
        perror("send");
        exit(EXIT_FAILURE);
    }
 
    char response[4096];
    ssize_t bytes_received = recv(client_socket, response, sizeof(response), 0);
    if (bytes_received == -1) 
    {
        perror("recv");
        exit(EXIT_FAILURE);
    }
 
    // Print the received response
    response[bytes_received] = '\0';
    printf("Received HTTP Response:\n%s\n", response);

    close(client_socket);
    return 0;
}