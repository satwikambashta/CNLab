// Write a concurrent TCP daytime server ‘C’ program. Along with the result, server
//should also send the process id to the client.
//SATWIK SAURAV(210905272)
//SERVER
#include<stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include<time.h>
#define PORTNO 10200


int main() {
    int sockfd, newsockfd, clilen, n = 1;
    char buf[256];
    time_t rawtime;
    struct sockaddr_in seraddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr =inet_addr("127.16.59.75");
    seraddr.sin_port = htons(PORTNO);

    bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));

    listen(sockfd, 5);

    while (1) {
        clilen = sizeof(cliaddr);
        printf("Server waiting \n");

        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);

        if (fork() == 0) 
        {
            printf("HERE");
            // Child process: get current time using time_t
            time(&rawtime);

            // Convert time_t to string format
            printf("time is %s",ctime(&rawtime));
            snprintf(buf, sizeof(buf), "%s", asctime(gmtime(&rawtime)));
            

            // Write the time to the client
            write(newsockfd, buf, strlen(buf));
            int serverPid = getpid();
            write(newsockfd, &serverPid, sizeof(int));

            close(newsockfd);
            exit(0);
        } else {
            close(newsockfd);
        }
    }

    close(sockfd);

    return 0;
}
