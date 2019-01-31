#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFSIZE 1024

int main(int argc, char *argv[])
{
    char* ip;
    int port;
    int client_sockfd = 0;
    int len = 0;
    if(argc < 3)
    {
        printf("Useage ./client <server-ip> <port>\n");
        return -1;
    }
    ip = argv[1];
    port = atoi(argv[2]);
    struct sockaddr_in server_addr;
    char buf[BUFFSIZE] = {0};
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);
    if((client_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket error!\n");
        return -1;
    }
    if(connect(client_sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0)
    {
        perror("Can not connect to server!\n");
        return -1;
    }
    printf("Connect success!\n");
    while(true)
    {
        printf("Enter string to send:");
        bzero(buf,BUFFSIZE);
        scanf("%s",buf);

        buf[strlen(buf)] = '\n';
        len = send(client_sockfd, buf, strlen(buf), 0);
        buf[len-1] = '\0';
        printf("Client: %s\n",buf);
        bzero(buf,BUFFSIZE);
        len = recv(client_sockfd, buf, BUFFSIZE, 0);
        buf[len-1] = '\0';
        printf("Server: %s\n",buf);
        close(client_sockfd);
        break;
    }
    return 0;
}
