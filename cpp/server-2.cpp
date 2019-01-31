#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

#define BUFFSIZE 1024

int main(int argc,char **argv)
{
    if(argc < 2)
    {
        printf("Useage ./server port\n");
        return -1;
    }
    int server_sockfd = 0;
    int client_sockfd = 0;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    char buf[BUFFSIZE] = {0};
    int len = 0;
    socklen_t sin_size = 0;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(atoi(argv[1]));

    if((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket error!\n");
        return -1;
    }
    printf("Listening on port %s\n",argv[1]);

    if(bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
    {
        perror("bind error!\n");
        return -1;
    }
    while(true)
    {
        printf("Waiting for client....\n");
        if(listen(server_sockfd, 1) < 0)
        {
            perror("listen error!\n");
            return -1;
        }
        sin_size= sizeof(struct sockaddr_in);
        if((client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &sin_size)) < 0)
        {
            perror("accept error!\n");
            return -1;
        }
        printf("accept client %s\n",inet_ntoa(client_addr.sin_addr));

        while((len = recv(client_sockfd, buf, BUFFSIZE, 0)) >0)
        {

            for(int i=0;i<len;i++)
            {
                if(buf[i]>='a'&&buf[i]<='z')
                {
                    buf[i] = toupper(buf[i]);
                }
            }

            if(send(client_sockfd, buf, len, 0) < 0)
            {
                perror("send error!\n");
                return -1;
            }
        }
        printf("Client disconnect!!\n");
        break;

    }


}
