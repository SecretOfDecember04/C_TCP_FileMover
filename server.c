#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1000

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen = sizeof(cli_addr);

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address structure
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));

    // Bind the socket
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    listen(sockfd, 5);
    printf("Server listening on port %s...\n", argv[1]);

    char buffer[BUFFER_SIZE];
    FILE *file;
    int bytes_read, total_bytes_received;
    char filename[256];

    while (1) {
        // Accept a connection
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0) {
            perror("Error accepting connection");
            continue;
        }

        while (1) {
            // Receive filename length
            uint32_t filename_len;
            bytes_read = read(newsockfd, &filename_len, sizeof(filename_len));
            if (bytes_read <= 0) {
                break;
            }
            filename_len = ntohl(filename_len);

            // Receive filename
            read(newsockfd, filename, filename_len);
            filename[filename_len] = '\0';

            // Receive file size
            uint32_t filesize;
            read(newsockfd, &filesize, sizeof(filesize));
            filesize = ntohl(filesize);

            // Open file for writing
            file = fopen(filename, "wb");
            if (!file) {
                perror("Error opening file for writing");
                continue;
            }

            // Receive file content
            total_bytes_received = 0;
            while (total_bytes_received < filesize) {
                bytes_read = read(newsockfd, buffer, BUFFER_SIZE);
                fwrite(buffer, 1, bytes_read, file);
                total_bytes_received += bytes_read;
            }

            fclose(file);

            // Send acknowledgment
            uint32_t total_bytes_sent = htonl(total_bytes_received);
            write(newsockfd, &total_bytes_sent, sizeof(total_bytes_sent));
        }

        close(newsockfd);
    }

    close(sockfd);
    return 0;
}
