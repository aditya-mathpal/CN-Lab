/*
To illustrate encryption and decryption of messages using TCP. The client accepts messages to be
encrypted through standard input device. The client will encrypt the string by adding 4 (random value)
to ASCII value of each alphabet. The encrypted message is sent to the server. The server then decrypts
the message and displays both encrypted and decrypted forms of the string. Program terminates after
one session.
*/
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<ctype.h>
#define PORTNO 12010

void decrypt(char *input, char *output) {
    int i;
    for (i = 0; input[i]; i++) {
        char ch = input[i];
        if (isalpha(ch-4)) output[i] = ch - 4;
        else output[i] = ch;
    }
    output[i] = 0;
}

int main() {
    int sockfd, newsockfd, n;
    struct sockaddr_in seraddr, cliaddr;
    socklen_t clilen;
    char buf[256], dec_msg[256];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);

    bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    listen(sockfd, 5);
    printf("Server started...\n");

    clilen = sizeof(cliaddr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);

    memset(buf, 0, sizeof(buf));
    n = read(newsockfd, buf, sizeof(buf));
    if (n > 0) {
        buf[n] = 0;
        decrypt(buf, dec_msg);
        printf("Encrypted message received: %s\n", buf);
        printf("Decrypted message: %s\n", dec_msg);

        char response[512];
        snprintf(response, sizeof(response), "Encrypted: %s\nDecrypted: %s", buf, dec_msg);
        write(newsockfd, response, strlen(response));
    }

    close(newsockfd);
    close(sockfd);
    return 0;
}

