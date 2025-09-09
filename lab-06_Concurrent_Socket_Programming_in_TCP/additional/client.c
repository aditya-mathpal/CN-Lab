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
    int sd, n;
    struct sockaddr_in address;
    char response[256];

    sd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);

    connect(sd, (struct sockaddr*)&address, sizeof(address));

    n = read(sd, response, sizeof(response)-1);
    response[n] = 0;

    printf("Server Response:\n%s", response);
    close(sd);

    return 0;
}

