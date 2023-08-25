/*to send manually crafted http request to web server */
//satwik saurav 210905272

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define PORTNO 443 // HTTPS port
#define HOST "api.github.com"
#define PATH "/repos/satwikambashta/satwikambashta"

void main() {
    int addrLen, result, sockID, i = 0, n;
    struct sockaddr_in addr;
    char buf[10000];

    sockID = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("140.82.112.4"); // GitHub's IP
    addr.sin_port = htons(PORTNO);
    addrLen = sizeof(addr);

    result = connect(sockID, (struct sockaddr *)&addr, addrLen);

    if (result == -1) {
        perror("\nCould not connect\n");
        exit(1);
    }

    char req[500];
    snprintf(req, sizeof(req), "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", PATH, HOST);

    write(sockID, req, strlen(req));

    n = read(sockID, buf, sizeof(buf));

    printf("Received : %s", buf);

    close(sockID);
}
