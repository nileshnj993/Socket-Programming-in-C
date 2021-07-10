#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

struct message {
    int size, palindrome;
    char string[50];
    int a, e, i, o, u;
};

int main() {

    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(8002);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(server.sin_zero, 0, sizeof(server.sin_zero));

    char sendBuff[50];
    struct message data;
    while(1) {
        printf("Enter string: ");
        scanf("%s", sendBuff);
        
        sendto(clientSocket, sendBuff, sizeof(sendBuff), 0, (struct sockaddr *) &server, sizeof(server));
        if(strcmp(sendBuff, "Halt") == 0) {
            break;
        }
        strcpy(sendBuff, "");

        socklen_t len = sizeof(server);
        int readBytes = recvfrom(clientSocket, (struct message *) &data, sizeof(data), 0, (struct sockaddr *) &server, &len);

        printf("Received string: %s \n", data.string);
        if(data.palindrome == 1) {
            printf("It is a palindrome\n");
        } else {
            printf("It is not a palindrome\n");
        }

        printf("Size of string: %d \n", data.size);
        printf("Vowel count: \n a: %d, e: %d, i: %d, o: %d, u: %d \n", data.a, data.e, data.i, data.o, data.u);
        printf("\n");

    }

    close(clientSocket);


}