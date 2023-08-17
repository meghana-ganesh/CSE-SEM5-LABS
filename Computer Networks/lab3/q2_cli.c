#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 80

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char request[1024];
    char response[4096];  // This size may need adjustment depending on the response size

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // Set up server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(sockfd);
        return 1;
    }

    // Craft HTTP GET request
    snprintf(request, sizeof(request),
             "GET / HTTP/1.1\r\n"
             "Host: %s\r\n"
             "\r\n",
             SERVER_IP);

    // Send HTTP request
    send(sockfd, request, strlen(request), 0);

    // Receive HTTP response
    ssize_t bytes_received = recv(sockfd, response, sizeof(response) - 1, 0);
    if (bytes_received == -1) {
        perror("Receive failed");
        close(sockfd);
        return 1;
    }

    // Null-terminate the received data
    response[bytes_received] = '\0';

    // Display HTTP response
    printf("HTTP Response:\n%s\n", response);

    // Close socket
    close(sockfd);

    return 0;
}
