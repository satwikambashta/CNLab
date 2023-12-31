/*Where the client accepts a sentence from the user and sends it to the server. The server
will check for duplicate words in the string. Server will find number of occurrences of
duplicate words present and remove the duplicate words by retaining single occurrence of
the word and send the resultant sentence to the client. The client displays the received
data on the client screen. The process repeats until the user enter the string “Stop”. Then
boththe processes terminate.*/
//satwik saurav(210905272)
//CLIENT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNO 10200

int main() {
    int sockfd, len, n = 1, result;
    struct sockaddr_in address;
    char sentence[256], received[256];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("172.16.59.75");
    address.sin_port = htons(PORTNO);
    result = connect(sockfd, (struct sockaddr*)&address, sizeof(address));

    if (result == -1) {
        perror("\nCLIENT ERROR");
        exit(1);
    }
    
    while (1) {
        printf("Enter a sentence (or 'Stop' to terminate): ");
        fgets(sentence, sizeof(sentence), stdin);
        sentence[strlen(sentence) - 1] = '\0';  // Remove newline character

        // Send the sentence to the server
        write(sockfd, sentence, strlen(sentence));
        
        if (strcmp(sentence, "Stop") == 0) {
            printf("Terminating client\n");
            break;
        }

        // Receive and display processed sentence from server
        n = read(sockfd, received, sizeof(received));
        received[n] = '\0';
        printf("Processed sentence received from server: %s\n", received);
    }

    // Close the socket
    close(sockfd);

    return 0;
}
