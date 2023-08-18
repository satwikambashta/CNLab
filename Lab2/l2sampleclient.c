//Write a TCP concurrent Echo server and simple client.
//CLIENT
//SATWIK SAURAV(210905272)

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int len, result, sockfd, n = 1;
    struct sockaddr_in address;
    char ch[256], buf[256];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("172.16.59.75");
    address.sin_port = htons(10200); //skippable. for windows to linux with different sizes or on different optic
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1)
    {
        perror("\nCLIENT ERROR");
        exit(1);
    }
    printf("\nENTER STRING\t");
    gets(ch);
    ch[strlen(ch)] = '\0';
    write(sockfd, ch, strlen(ch));
    int serverPid;
    read(sockfd, &serverPid, sizeof(int));//display process id
    printf("(Process ID: %d):\n", serverPid);
    printf("STRING SENT BACK FROM SERVER IS ..... ");
    while (n)
    {
        n = read(sockfd, buf, sizeof(buf));
        puts(buf);
    }
    
}
