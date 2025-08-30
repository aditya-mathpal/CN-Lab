#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNO 12010

int main() {
    int sockfd, n, rows, cols;
    struct sockaddr_in seraddr;
    socklen_t len;
    char buf[256], sendBuf[256];
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);
    len = sizeof(seraddr);
    
    printf("number of rows: ");
    scanf("%d", &rows);
    printf("number of columns: ");
    scanf("%d", &cols);
    
    sprintf(sendBuf, "DIMENSIONS %d %d", rows, cols);
    sendto(sockfd, sendBuf, strlen(sendBuf), 0,
           (struct sockaddr *)&seraddr, len);
    
    for(int i = 0; i < rows; i++) {
        printf("Enter row %d: ", i+1);
        strcpy(sendBuf, "ROW ");
        
        for(int j = 0; j < cols; j++) {
            int element;
            scanf("%d", &element);
            char temp[20];
            sprintf(temp, "%d ", element);
            strcat(sendBuf, temp);
        }
        
        sendto(sockfd, sendBuf, strlen(sendBuf), 0,
               (struct sockaddr *)&seraddr, len);
    }
    
    memset(buf, 0, sizeof(buf));
    n = recvfrom(sockfd, buf, sizeof(buf), 0,
                 (struct sockaddr *)&seraddr, &len);
    if(n > 0) buf[n] = 0;
    
    strcpy(sendBuf, "STOP");
    sendto(sockfd, sendBuf, strlen(sendBuf), 0,
           (struct sockaddr *)&seraddr, len);
    
    close(sockfd);
    return 0;
}
