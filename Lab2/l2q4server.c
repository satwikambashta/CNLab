//  Write a concurrent TCP client server ‘C’ program where the client accepts a 
// sentence from the user and sends it to the server. The server will check for duplicate 
// words in the string. Server will find the number of occurrences of duplicate words 
// present and remove the duplicate words by retaining single occurrence of the word and 
// send the resultant sentence to the client.
//satwik saurav 210905272
//SERVER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#define PORTNO 10200


int main() {
    int sockfd, newsockfd, clilen, n = 1;
    struct sockaddr_in seraddr, cliaddr;
    int i, value;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("172.16.59.75");
    seraddr.sin_port = htons(PORTNO);

    bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));
    listen(sockfd, 5);

    while (1) {
        char buf[256];
        printf("Server waiting...\n");
        clilen = sizeof(cliaddr);
        newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);
        if (fork() == 0)
        {

            // Read sentence from client
            n = read(newsockfd, buf, sizeof(buf));
            buf[n] = '\0';
            printf("Received sentence from client: %s\n", buf);
    
            if (strcmp(buf, "Stop") == 0) {
                printf("Client requested to stop. Terminating server...\n");
                break;
            }
    
            // Remove duplicate words
            char result[256] = "";
            char* words[256];
            int wordCount = 0;
    
            char* token = strtok(buf, " ");
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
    
            strcpy(buf, result);
            printf("Processed sentence: %s\n", buf);
            
            // Send back the modified sentence
            n = write(newsockfd, buf, sizeof(buf));
    
            // Close the new socket
            close(newsockfd);
        }
    
    else
        {
            close(newsockfd);
            wait(NULL);
        }
  }
    // Close the server socket
    close(sockfd);
    return 0;
}
