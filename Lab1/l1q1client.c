// To illustrate encryption and decryption of messages using TCP. The client accepts
// messages to be encrypted through standard input device. The client will encrypt the string
// by adding 4(random value) to ASCII value of each alphabet. The encrypted message is
// sent to the server. The server then decrypts the message and displays both encrypted and
// decrypted forms of the string. Program terminates after one session.
//CLIENT
//satwik saurav(210905272)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORTNO 10200

int main()
{
    int sockfd,len,n=1,result;
    struct sockaddr_in address;
    char ch[256],buf[256],encrypt[256];

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("172.16.59.75");
    address.sin_port = htons(PORTNO);
    result = connect(sockfd,(struct sockaddr*)&address,sizeof(address));

    if(result==-1){
        perror("\nCLIENT ERROR");
        exit(1);
    }
    printf("\nENTER STRING\t");
    gets(ch);
    ch[strlen(ch)]='\0';
    for(int i=0;i<strlen(ch);i++)
        ch[i]+= 4;

    write(sockfd,ch,strlen(ch));
    printf("encrypted message sent from client(me):%s",ch);
    printf("\ndecrypted message sent by server is:");

    while(n){
        n=read(sockfd,buf,sizeof(buf));
        puts(buf);
    }
}