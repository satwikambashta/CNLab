#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNO 10200

void removeDuplicates(char* sentence) {
    char result[256] = "";
    char* words[256];
    int wordCount = 0;

    char* token = strtok(sentence, " ");
    while (token != NULL) {
        int isDuplicate = 0;
        for (int i = 0; i < wordCount; i++) {
            if (strcmp(words[i], token) == 0) {
                isDuplicate = 1;
                break;
            }
        }

        if (!isDuplicate) {
            strcat(result, token);
            strcat(result, " ");
            words[wordCount++] = strdup(token);
        }

        token = strtok(NULL, " ");
    }

    strcpy(sentence, result);
}

int main() {
    int sockfd, newsockfd, portno, clilen, n = 1;
    struct sockaddr_in seraddr, cliaddr;
    int i, value;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("172.16.59.34");
    // seraddr.sin_addr.s_addr = INADDR_ANY;  Listen on all available interfaces
    seraddr.sin_port = htons(PORTNO);

    bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));
    listen(sockfd, 5);

    while (1) {
        char buf[256];
        printf("Server waiting...\n");
        clilen = sizeof(cliaddr);
        newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);

        // Read sentence from client
        n = read(newsockfd, buf, sizeof(buf));
        buf[n] = '\0';
        printf("Received sentence from client: %s\n", buf);

        // Process sentence (remove duplicates) and send response
        if (strcmp(buf, "Stop") == 0) {
            printf("Client requested to stop. Terminating server...\n");
            write(newsockfd, "Terminating server...", strlen("Terminating server..."));
            close(newsockfd);
            break;
        } else {
            removeDuplicates(buf);
            printf("Processed sentence: %s\n", buf);
            n = write(newsockfd, buf, sizeof(buf));
        }

        // Close the new socket
        close(newsockfd);
    }

    // Close the server socket
    close(sockfd);

    return 0;
}
