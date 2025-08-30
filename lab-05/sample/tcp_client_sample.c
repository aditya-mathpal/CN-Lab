#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORTNO 12010

int main() {
    int len, result, sockfd, n = 1;
    struct sockaddr_in address;
    char ch[256], buf[256];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);
    len = sizeof(address);

    result = connect(sockfd, (struct sockaddr *)&address, len);
    if(result == -1) {
        perror("\nclient error");
        exit(1);
    }
    printf("\nenter string: ");
    fgets(ch, 100, stdin);
    ch[strlen(ch)] = 0;
    write(sockfd, ch, strlen(ch));
    printf("string bounced back from server: ");
    while(n) {
        n = read(sockfd, buf, sizeof(buf));
        puts(buf);
    }
    close(sockfd);
}