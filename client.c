#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1000

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <Server IP> <Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd;
    struct sockaddr_in serv_addr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address structure
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
        perror("Invalid address or Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error connecting stream socket");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    char filename[256];
    FILE *file;
    int bytes_read, total_bytes_sent;

    while (1) {
        printf("Enter filename to transfer (or DONE to exit): ");
        scanf("%s", filename);

        if (strcmp(filename, "DONE") == 0) {
            break;
        }

        // Open the file
        file = fopen(filename, "rb");
        if (!file) {
            perror("Error opening file");
            continue;
        }

        // Send filename size and name
        uint32_t filename_len = htonl(strlen(filename));
        write(sockfd, &filename_len, sizeof(filename_len));
        write(sockfd, filename, strlen(filename));

        // Get file size and send it
        fseek(file, 0, SEEK_END);
        uint32_t filesize = htonl(ftell(file));
        rewind(file);
        write(sockfd, &filesize, sizeof(filesize));

        // Send file content in chunks
        total_bytes_sent = 0;
        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
            write(sockfd, buffer, bytes_read);
            total_bytes_sent += bytes_read;
        }

        fclose(file);

        // Receive and print the acknowledgment from server
        uint32_t total_bytes_received;
        read(sockfd, &total_bytes_received, sizeof(total_bytes_received));
        total_bytes_received = ntohl(total_bytes_received);
        printf("Server received %u bytes.\n", total_bytes_received);
    }

    close(sockfd);
    return 0;
}
