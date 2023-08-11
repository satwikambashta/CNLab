/*Write a TCP concurrent client server program where server accepts integer array from
client and sorts it and returns it to the client along with process id
CLIENT*/

//SATWIK SAURAV(210905272)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNO 10200
#define MAX_ARRAY_SIZE 100

int main() {
    int sockfd, len, n, result;
    struct sockaddr_in address;
    int arr[MAX_ARRAY_SIZE];
    int size;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.16.59.34");
    address.sin_port = htons(PORTNO);
    result = connect(sockfd, (struct sockaddr*)&address, sizeof(address));

    if (result == -1) {
        perror("\nCLIENT ERROR");
        exit(1);
    }

    printf("Enter the size of the integer array: ");
    scanf("%d", &size);

    printf("Enter %d integers:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    // array size
    write(sockfd, &size, sizeof(int));

    // Send array
    write(sockfd, arr, sizeof(int) * size);

    //process ID 
    int serverPid;
    read(sockfd, &serverPid, sizeof(int));

    //sorted array
    n = read(sockfd, arr, sizeof(int) * size);

    printf("Sorted array received from server (Process ID: %d):\n", serverPid);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    close(sockfd);

    return 0;
}
