/*Write a UDP client-server program where t he client sends rows of a matrix, and the
servercombines them together as a matrix*/

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{
    int sd;
    char buf[25];
    struct sockaddr_in sadd, cadd;
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    sadd.sin_family = AF_INET;
    sadd.sin_addr.s_addr = inet_addr("172.16.59.75"); 
    sadd.sin_port = htons(9704);
    int len = sizeof(cadd);
    int result = bind(sd, (struct sockaddr *)&sadd, sizeof(sadd));
    int m;

    recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr *)&cadd, &len);
    printf("%d",m);

    // int m = recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr *)&cadd, &len);
    // printf("the server send is\n");
    // puts(buf);
    // int n = sendto(sd, buf, sizeof(buf), 0, (struct sockaddr *)&cadd, len);
    return 0;
}