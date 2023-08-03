//udp matrix rows
//server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 12345
#define MAX_ROWS 10
#define MATRIX_SIZE 100

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address struct
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket to the specified address and port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Socket binding failed");
        exit(EXIT_FAILURE);
    }

    int matrix[MAX_ROWS][MATRIX_SIZE];
    int row_counter = 0;

    printf("Server waiting for data...\n");

    while (1) {
        int received_bytes = recvfrom(server_socket, matrix[row_counter], sizeof(matrix[row_counter]), 0,
                                     (struct sockaddr *)&client_addr, &addr_len);

        if (received_bytes == -1) {
            perror("Data receive failed");
            exit(EXIT_FAILURE);
        }

        if (received_bytes == 0) {
            printf("Client disconnected.\n");
            break;
        }

        printf("Received row %d\n", row_counter);
        row_counter++;

        if (row_counter == MAX_ROWS) {
            printf("Matrix is complete.\n");
            break;
        }
    }

    // Print the received matrix
    printf("Received Matrix:\n");
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    close(server_socket);

    return 0;
}
