/*Implement concurrent Remote Math Server To perform arithmetic operations in the
server and display the result to the client. The client accepts two integers and an
operator from the user and sends it to the server. The server then receives integers and
operator. The server will perform the operation on integers and sends the result back
to the client which is displayed on the client screen. Then both the processes
terminate.
SERVER*/

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
    int sockfd, len, n, result;
    struct sockaddr_in address;
    int a,b;
    char o;
    int outp;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.16.59.75");
    address.sin_port = htons(PORTNO);
    result = connect(sockfd, (struct sockaddr*)&address, sizeof(address));

    if (result == -1) {
        perror("\nCLIENT ERROR");
        exit(1);
    }

    printf("Enter first number: ");
    scanf("%d", &a);
    write(sockfd, &a, sizeof(int));
    printf("Enter second number: ");
    scanf("%d", &b);
    write(sockfd, &b, sizeof(int));
    printf("Enter operation (+,-,*,/): ");
    scanf(" %c",&o);
    write(sockfd, &o, sizeof(char));


    read(sockfd, &outp, sizeof(int));
    printf("The soution is %d", outp);

    printf("\n");
    close(sockfd);

    return 0;
}
