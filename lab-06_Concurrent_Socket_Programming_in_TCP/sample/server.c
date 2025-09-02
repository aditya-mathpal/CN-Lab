#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORTNO 10200

int main() {
    int sockfd, newsockfd, portno, clilen, n = 1;
    char buf[256];
    struct sockaddr_in seraddr, cliaddr;
    int i, value;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));
    listen(sockfd, 5);
    while(1) {
        clilen = sizeof(cliaddr);
        newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);
        if(fork() == 0) {
            n = read(newsockfd, buf, sizeof(buf));
            buf[n] = 0;
            printf("message from client: \"%s\"\n", buf);
            n = write(newsockfd, buf, n);
            close(newsockfd);
            exit(0);
        }
        else close(newsockfd);
    }
}
