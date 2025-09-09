/*
Write a client program to send a manually crafted HTTP request packet to a Web Server and display
all fields received in HTTP Response at client Side.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 80

int main() {
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char send_buf[1024], recv_buf[4096];

    const char *hostname = "www.google.com";

    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr, "ERROR: No such host\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation error");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        exit(1);
    }

    snprintf(send_buf, sizeof(send_buf),
        "GET / HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Connection: close\r\n\r\n", hostname);

    write(sockfd, send_buf, strlen(send_buf));

    while ((n = read(sockfd, recv_buf, sizeof(recv_buf)-1)) > 0) {
        recv_buf[n] = 0;
        printf("%s", recv_buf);
    }

    close(sockfd);
    return 0;
}

/*
output:
HTTP/1.1 200 OK
Date: Tue, 09 Sep 2025 06:35:11 GMT
...
*/
