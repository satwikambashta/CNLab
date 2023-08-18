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

int main()
{
    int sockfd, newsockfd, portno, clilen, n;
    struct sockaddr_in seraddr, cliaddr;
    int a,b, temp=0;
    char op;
    int outp;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr =inet_addr("127.16.59.75");
    seraddr.sin_port = htons(PORTNO);

    bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    listen(sockfd, 5);

    while (1)
    {
        printf("Server waiting...\n");
        clilen = sizeof(cliaddr);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);

        if (fork() == 0)
        {
            read(newsockfd, &a, sizeof(int));
            read(newsockfd, &b, sizeof(int));
            read(newsockfd, &op, sizeof(char));
            printf("%d %c %d",a,op,b);
            if(op=='+'){
                temp=a+b;
            }
            else if(op=='*'){
                temp=a*b;
            }
            else if(op=='-'){
                temp=a-b;
            }
            else if(op=='/'){
                temp=a/b;
            }
            else{
                printf("Invalid operation");
            }
            outp=temp;
            write(newsockfd, &outp, sizeof(int));
            close(newsockfd); 
            exit(0);
        }
        else{
            close(newsockfd); // Close the socket in the parent process
            wait(NULL);   
        }
    }
    close(sockfd);
    return 0;
}

