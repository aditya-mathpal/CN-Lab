/*
Write a concurrent TCP client server ‘C’ program where the client accepts a sentence from the user
and sends it to the server. The server will check for duplicate words in the string. Server will find the
number of occurrences of duplicate words present and remove the duplicate words by retaining single
occurrence of the word and send the resultant sentence to the client.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <ctype.h>

#define PORTNO 10200

void toLowerCase(char *str) {
    for(int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void removeDuplicates(char *sentence, char *result) {
    char words[1000][100];
    char temp[1000];
    int wordCount = 0;
    int duplicates = 0;
    
    strcpy(temp, sentence);
    char *token = strtok(temp, " \t\n");
    
    while(token != NULL) {
        char lowerToken[100];
        strcpy(lowerToken, token);
        toLowerCase(lowerToken);
        
        int isDuplicate = 0;
        for(int i = 0; i < wordCount; i++) {
            char lowerWord[100];
            strcpy(lowerWord, words[i]);
            toLowerCase(lowerWord);
            if(strcmp(lowerWord, lowerToken) == 0) {
                isDuplicate = 1;
                duplicates++;
                break;
            }
        }
        
        if(!isDuplicate) {
            strcpy(words[wordCount], token);
            wordCount++;
        }
        
        token = strtok(NULL, " \t\n");
    }
    
    printf("Found %d duplicate words\n", duplicates);
    
    strcpy(result, "");
    for(int i = 0; i < wordCount; i++) {
        strcat(result, words[i]);
        if(i < wordCount - 1) strcat(result, " ");
    }
    strcat(result, "\n");
}

int main() {
    int sockfd, newsockfd, clilen, n;
    char buf[1000], result[1000];
    struct sockaddr_in seraddr, cliaddr;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);
    
    bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));
    listen(sockfd, 5);
    
    printf("Server started...\n");
    
    while(1) {
        clilen = sizeof(cliaddr);
        newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);
        
        if(fork() == 0) {
            n = read(newsockfd, buf, sizeof(buf));
            buf[n] = 0;
            
            printf("Received sentence.\n");
            
            removeDuplicates(buf, result);
            
            write(newsockfd, result, strlen(result));
            close(newsockfd);
            exit(0);
        }
        else close(newsockfd);
    }
    return 0;
}
