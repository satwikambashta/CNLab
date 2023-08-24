/*Write a UDP client-server program where t he client sends rows of a matrix, and the
servercombines them together as a matrix*/
//210905272 satwiksaurav
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define PORTNO 10200

void main() {
    int status, rows, cols, clientAddrLen;
    struct sockaddr_in serverAddr, clientAddr;
    int sockID = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("172.16.59.33"); 
    serverAddr.sin_port = htons(PORTNO);
    bind(sockID, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    int arr[100];

    recvfrom(sockID, arr, sizeof(arr), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);

    rows = arr[0];
    cols = arr[1];

    int mat[rows][cols]; // Using a static 2D array

    for (int i = 0; i < rows; i++) {
        recvfrom(sockID, arr, sizeof(arr), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
        for (int j = 0; j < cols; j++)
            mat[i][j] = arr[j];
    }

    printf("The matrix formed is: \n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }

}
