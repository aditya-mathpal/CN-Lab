#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#define PORTNO 10200

int main() {
    int sd;
    struct sockaddr_in address;
    sd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);
    connect(sd, (struct sockaddr*)&address, sizeof(address));
    char buf[25], buf1[25];
    printf("enter buf:\n");
    fgets(buf, 25, stdin);
    int len = sizeof(address);
    int m = write(sd, buf, strlen(buf));
    int n = read(sd, buf1, sizeof(buf1)-1);
    buf1[n] = 0;
    printf("the server echo is\n");
    puts(buf1);
    return 0;
}
