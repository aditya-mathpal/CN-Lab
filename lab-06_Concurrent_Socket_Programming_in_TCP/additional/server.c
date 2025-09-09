/*
Write a concurrent TCP daytime server ‘C’ program. Along with the result, server should also send
the process id to the client.
*/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>

#define PORTNO 10200

int main() {
    int sockfd, newsockfd, clilen, n;
    struct sockaddr_in seraddr, cliaddr;
    char result[256];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);

    bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));
    listen(sockfd, 5);

    printf("Server started...\n");

    while(1) {
        clilen = sizeof(cliaddr);
        newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);

        if (fork() == 0) {
            close(sockfd);

            time_t now = time(NULL);
            struct tm *tm_info = localtime(&now);
            char time_str[128];
            strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);

            snprintf(result, sizeof(result), "Date and Time: %s\nProcess ID: %d\n", time_str, getpid());

            write(newsockfd, result, strlen(result));
            close(newsockfd);
            exit(0);
        } else {
            close(newsockfd);
            waitpid(-1, NULL, WNOHANG);
        }
    }

    close(sockfd);
    return 0;
}

