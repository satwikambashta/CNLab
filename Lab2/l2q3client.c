//concurrent daytimeserver
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#define PORTNO 13

int main() {
    int sockfd, n, result;
    char buf[256];
    struct sockaddr_in seraddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address
    seraddr.sin_port = htons(PORTNO);

    result= connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));

    read(sockfd, buf, sizeof(buf));

    printf("Current date and time: %s\n", buf);

    int serverPid;
    read(sockfd, &serverPid, sizeof(int));//display process id
    printf("(Process ID: %d):\n", serverPid);
  

    close(sockfd);

    return 0;
}
