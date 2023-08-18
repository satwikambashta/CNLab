/*Write a UDP client-server program where t he client sends rows of a matrix, and the
servercombines them together as a matrix*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sd;
    int m,n;
    struct sockaddr_in address;
    
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("172.16.59.75"); 
    address.sin_port = htons(9704);
    printf("Enter number of rows ");
    scanf("%d",&m);
    // printf("%d",m);
    printf("Enter number of columns: ");
    scanf("%d",&n);
    int len = sizeof(address);
    sendto(sd, &m, sizeof(m), 0, (struct sockaddr *)&address, len);
    int arr[n];
    for(int i=0; i<m; i++)
    {
        printf("Enter values of row %d",i);
        for(int j=0; j<n; j++){
            scanf("%d",arr[j]);

        }

    }
    
    
    // int m = sendto(sd, buf, sizeof(buf), 0, (struct sockaddr *)&address, len);
    // int n = recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr *)&address, &len);
    
    return 0;
}