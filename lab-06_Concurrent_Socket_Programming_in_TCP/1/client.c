#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNO 10200

int main() {
    int sd;
    struct sockaddr_in address;
    char request[50], response[50];
    int num1, num2;
    char operator;
    
    sd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);
    
    connect(sd, (struct sockaddr*)&address, sizeof(address));
    
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &operator);
    printf("Enter second number: ");
    scanf("%d", &num2);
    
    sprintf(request, "%d %c %d", num1, operator, num2);
    
    write(sd, request, strlen(request));
    int n = read(sd, response, sizeof(response)-1);
    response[n] = 0;
    
    printf("Result: %s\n", response);
    
    close(sd);
    return 0;
}
