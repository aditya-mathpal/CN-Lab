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
    
    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);
    len = sizeof(seraddr);
    
    printf("UDP Client - Matrix Row Sender\n");
    
    // Get matrix dimensions
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);
    
    // Send dimensions to server
    sprintf(sendBuf, "DIMENSIONS %d %d", rows, cols);
    sendto(sockfd, sendBuf, strlen(sendBuf), 0,
           (struct sockaddr *)&seraddr, len);
    
    // Wait for server acknowledgment
    memset(buf, 0, sizeof(buf));
    n = recvfrom(sockfd, buf, sizeof(buf), 0,
                 (struct sockaddr *)&seraddr, &len);
    if(n > 0) {
        buf[n] = '\0';
        printf("Server response: %s\n", buf);
    }
    
    // Send each row
    for(int i = 0; i < rows; i++) {
        printf("\nEnter row %d (%d elements): ", i+1, cols);
        strcpy(sendBuf, "ROW ");
        
        for(int j = 0; j < cols; j++) {
            int element;
            scanf("%d", &element);
            char temp[20];
            sprintf(temp, "%d ", element);
            strcat(sendBuf, temp);
        }
        
        // Send row to server
        sendto(sockfd, sendBuf, strlen(sendBuf), 0,
               (struct sockaddr *)&seraddr, len);
        
        // Wait for acknowledgment
        memset(buf, 0, sizeof(buf));
        n = recvfrom(sockfd, buf, sizeof(buf), 0,
                     (struct sockaddr *)&seraddr, &len);
        if(n > 0) {
            buf[n] = '\0';
            printf("Server response: %s\n", buf);
        }
    }
    
    // Receive complete matrix from server
    printf("\nWaiting for complete matrix from server...\n");
    memset(buf, 0, sizeof(buf));
    n = recvfrom(sockfd, buf, sizeof(buf), 0,
                 (struct sockaddr *)&seraddr, &len);
    if(n > 0) {
        buf[n] = '\0';
        printf("Complete matrix from server:\n%s\n", buf);
    }
    
    // Send stop signal
    strcpy(sendBuf, "STOP");
    sendto(sockfd, sendBuf, strlen(sendBuf), 0,
           (struct sockaddr *)&seraddr, len);
    
    // Wait for goodbye message
    memset(buf, 0, sizeof(buf));
    n = recvfrom(sockfd, buf, sizeof(buf), 0,
                 (struct sockaddr *)&seraddr, &len);
    if(n > 0) {
        buf[n] = '\0';
        printf("Server response: %s\n", buf);
    }
    
    close(sockfd);
    return 0;
}
