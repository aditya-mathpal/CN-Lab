#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNO 12010

int main() {
    int sockfd, n, rows = 0, cols = 0;
    struct sockaddr_in seraddr, cliaddr;
    socklen_t clilen;
    char buf[256];
    int matrix[10][10];
    int currentRow = 0;
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);
    
    bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    
    printf("server ready...\n");

    while(1) {
        clilen = sizeof(cliaddr);
        memset(buf, 0, sizeof(buf));
        
        n = recvfrom(sockfd, buf, sizeof(buf), 0, 
                    (struct sockaddr *)&cliaddr, &clilen);
        
        if(n > 0) {
            buf[n] = 0;
            
            if(strncmp(buf, "DIMENSIONS", 10) == 0) {
                sscanf(buf, "DIMENSIONS %d %d", &rows, &cols);
                currentRow = 0;
                
                strcpy(buf, "READY");
                sendto(sockfd, buf, strlen(buf), 0,
                       (struct sockaddr *)&cliaddr, clilen);
            }

            else if(strncmp(buf, "ROW", 3) == 0) {
                char *token;
                int col = 0;
                
                token = strtok(buf + 4, " ");
                while(token != NULL && col < cols) {
                    matrix[currentRow][col] = atoi(token);
                    col++;
                    token = strtok(NULL, " ");
                }
                
                currentRow++;
                
                if(currentRow == rows) {
                    printf("\nComplete Matrix:\n");
                    for(int i = 0; i < rows; i++) {
                        for(int j = 0; j < cols; j++) {
                            printf("%d\t", matrix[i][j]);
                        }
                        printf("\n");
                    }
                    printf("\n");
                    
                    char matrixStr[1024] = "MATRIX\n";
                    char temp[50];
                    for(int i = 0; i < rows; i++) {
                        for(int j = 0; j < cols; j++) {
                            sprintf(temp, "%d\t", matrix[i][j]);
                            strcat(matrixStr, temp);
                        }
                        strcat(matrixStr, "\n");
                    }
                    
                    sendto(sockfd, matrixStr, strlen(matrixStr), 0,
                           (struct sockaddr *)&cliaddr, clilen);
                }
            }
            else if(strcmp(buf, "STOP") == 0) {
                strcpy(buf, "GOODBYE");
                sendto(sockfd, buf, strlen(buf), 0,
                       (struct sockaddr *)&cliaddr, clilen);
                break;
            }
        }
    }
    
    close(sockfd);
    return 0;
}
