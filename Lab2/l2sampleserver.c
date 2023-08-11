//SERVER
//SATWIK SAURAV(210905272)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORTNO 10200

int main()
{
    int sockfd, newsockfd, portno, clilen, n = 1;
    char buf[256];
    struct sockaddr_in seraddr, cliaddr;
    int i, value;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("172.16.59.75");
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    listen(sockfd, 5);
    while (1)
    {
        clilen = sizeof(clilen);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
        // child or parent
        if (fork() == 0)
        {
            n = read(newsockfd, buf, sizeof(buf));
            int serverPid = getpid();
            write(newsockfd, &serverPid, sizeof(int));
            printf("Message from client: %s\n", buf);
            n = write(newsockfd, buf, sizeof(buf));
            close(newsockfd);
            exit(0);
        }
        else
        {
            close(newsockfd);
            wait(NULL);
        }
    }

    return 0;
}