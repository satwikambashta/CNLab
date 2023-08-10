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
#define MAX_ARRAY_SIZE 100

int main()
{
    int sockfd, newsockfd, portno, clilen, n;
    struct sockaddr_in seraddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = INADDR_ANY;
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
            close(sockfd); // Close the listening socket in the child process

            int arr[MAX_ARRAY_SIZE];
            int size;

            // array size
            read(newsockfd, &size, sizeof(int));

            // array
            n = read(newsockfd, arr, sizeof(int) * size);
            printf("Received array from client\n");

            // Sort
            for (int i = 0; i < size - 1; i++)
            {
                for (int j = 0; j < size - i - 1; j++)
                {
                    if (arr[j] > arr[j + 1])
                    {
                        int temp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = temp;
                    }
                }
            }

            // Send the sorted array and process ID to the client
            int serverPid = getpid();
            write(newsockfd, &serverPid, sizeof(int));
            write(newsockfd, arr, sizeof(int) * size);

            // Close the child socket and exit
            close(newsockfd);
            exit(0);
        }
        else
        {
            close(newsockfd); // Close the socket in the parent process
            wait(NULL);       // Wait for the child process to finish
        }
    }

    close(sockfd);
    return 0;
}
