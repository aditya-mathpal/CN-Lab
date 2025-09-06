/*
Implement concurrent Remote Math Server To perform arithmetic operations in the server and
display the result to the client. The client accepts two integers and an operator from the user and sends
it to the server. The server then receives integers and operator. The server will perform the operation on
integers and sends the result back to the client which is displayed on the client screen. Then both the
processes terminate.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#define PORTNO 10200

int main() {
    int sockfd, newsockfd, clilen, n;
    char buf[256], result[256];
    struct sockaddr_in seraddr, cliaddr;
    int num1, num2;
    char operator;
    double res;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);
    
    bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));
    listen(sockfd, 5);
    
    printf("Remote Math Server started...\n");
    
    clilen = sizeof(cliaddr);
    newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);
    
    if(fork() == 0) {
        n = read(newsockfd, buf, sizeof(buf));
        buf[n] = 0;
        
        sscanf(buf, "%d %c %d", &num1, &operator, &num2);
        
        switch(operator) {
            case '+': res = num1 + num2; break;
            case '-': res = num1 - num2; break;
            case '*': res = num1 * num2; break;
            case '/': res = (double)num1 / num2; break;
            default:
                strcpy(result, "Error");
                write(newsockfd, result, strlen(result));
                close(newsockfd);
                exit(0);
        }
        
        if(operator == '/')
            sprintf(result, "%.2f", res);
        else
            sprintf(result, "%.0f", res);
        
        write(newsockfd, result, strlen(result));
        close(newsockfd);
        exit(0);
    }
    else {
        close(newsockfd);
        wait(NULL);
        printf("Server terminating.\n");
    }
    
    close(sockfd);
    return 0;
}
