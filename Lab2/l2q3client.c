//concurrent daytimeserver
//satwik saurav 210905272


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORTNO 10200

int main() {
    int sockfd, n, result;
    int serverPid;
    char buf[256];
    struct sockaddr_in seraddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.16.59.75"); // Server IP address
    seraddr.sin_port = htons(PORTNO);

    result= connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));

    read(sockfd, buf, sizeof(buf));

    printf("Current date and time: %s\n", buf);

    
    read(sockfd, &serverPid, sizeof(int));//display process id
    printf("(Process ID: %d):\n", serverPid);
  

    close(sockfd);

    return 0;
}
