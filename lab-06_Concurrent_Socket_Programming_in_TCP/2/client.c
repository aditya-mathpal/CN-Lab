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
    char sentence[1000], result[1000];
    
    sd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);
    
    connect(sd, (struct sockaddr*)&address, sizeof(address));
    
    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);
    
    write(sd, sentence, strlen(sentence));
    int n = read(sd, result, sizeof(result)-1);
    result[n] = '\0';
    
    printf("Processed sentence: %s", result);
    
    close(sd);
    return 0;
}
