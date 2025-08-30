#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNO 12010

int main() {
    int len, result, sockfd, n;
    struct sockaddr_in address;
    char ch[256], buf[256];
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);
    len = sizeof(address);
    
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if(result == -1) {
        perror("Client connection error");
        exit(1);
    }
    
    printf("Connected to server. Enter sentences (type 'Stop' to quit):\n");
    
    while(1) {
        printf("\nEnter sentence: ");
        fgets(ch, sizeof(ch), stdin);
        
        ch[strcspn(ch, "\n")] = 0;
        
        write(sockfd, ch, strlen(ch));
        
        if(strcmp(ch, "Stop") == 0) {
            printf("Stopping client...\n");
            break;
        }
        
        memset(buf, 0, sizeof(buf));
        n = read(sockfd, buf, sizeof(buf));
        if(n > 0) {
            buf[n] = 0;
            printf("Processed sentence from server: %s\n", buf);
        }
    }
    
    close(sockfd);
    return 0;
}
