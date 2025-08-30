#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>

#define PORTNO 12010

void toLowerCase(char *str) {
    for(int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void removeDuplicates(char *sentence, char *result) {
    char words[100][50];
    int wordCount = 0;
    int duplicateCount = 0;
    
    char *token = strtok(sentence, " \t\n");
    while(token != NULL && wordCount < 100) {
        strcpy(words[wordCount], token);
        toLowerCase(words[wordCount]);
        wordCount++;
        token = strtok(NULL, " \t\n");
    }
    
    strcpy(result, "");
    for(int i = 0; i < wordCount; i++) {
        int isDuplicate = 0;

        for(int j = 0; j < i; j++) {
            if(strcmp(words[i], words[j]) == 0) {
                isDuplicate = 1;
                duplicateCount++;
                break;
            }
        }
        
        if(!isDuplicate) {
            if(strlen(result) > 0) {
                strcat(result, " ");
            }
            strcat(result, words[i]);
        }
    }
    
    printf("Number of duplicate words removed: %d\n", duplicateCount);
}

int main() {
    int sockfd, newsockfd, clilen, n;
    struct sockaddr_in seraddr, cliaddr;
    char buf[256], result[256];
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);
    
    bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    listen(sockfd, 5);
    
    while(1) {
        printf("Server waiting for connection...\n");
        clilen = sizeof(cliaddr);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
        
        while(1) {
            memset(buf, 0, sizeof(buf));
            n = read(newsockfd, buf, sizeof(buf));
            
            if(n <= 0) break;
            
            buf[n] = 0;
            printf("Message from client: %s\n", buf);
            
            if(strcmp(buf, "Stop") == 0) {
                printf("Client requested to stop. Closing connection.\n");
                break;
            }
            
            char tempBuf[256];
            strcpy(tempBuf, buf);
            removeDuplicates(tempBuf, result);
            
            printf("Processed sentence: %s\n", result);
            
            write(newsockfd, result, strlen(result));
        }
        
        close(newsockfd);
        printf("Client disconnected.\n");
    }
    
    close(sockfd);
    return 0;
}
