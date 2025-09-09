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

void encrypt(char *input, char *output) {
    int i;
    for (i = 0; input[i]; i++) {
        char ch = input[i];
        if (isalpha(ch)) output[i] = ch + 4;
        else output[i] = ch;
    }
    output[i] = 0;
}

int main() {
    int sockfd, n;
    struct sockaddr_in address;
    char message[256], enc_msg[256], buf[256];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);

    if (connect(sockfd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("Connection error");
        return 1;
    }

    printf("Enter a message to encrypt and send: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;

    encrypt(message, enc_msg);

    write(sockfd, enc_msg, strlen(enc_msg));

    memset(buf, 0, sizeof(buf));
    n = read(sockfd, buf, sizeof(buf));
    if (n > 0) {
        buf[n] = 0;
        printf("Server response:\n%s\n", buf);
    }

    close(sockfd);
    return 0;
}

