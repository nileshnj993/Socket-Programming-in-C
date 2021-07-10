#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main() {

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(8001);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(server.sin_zero, 0, sizeof(server.sin_zero));

    if (connect(clientSocket, (struct sockaddr*) &server, sizeof(server)) < 0) {
        printf("Can't connect to server");
        exit(0); close(clientSocket);
    } else {
        printf("Connected to server!\n");
    }

    char sendBuff[50];
    char recvBuff[50];
    while(1) {
        printf("Enter message: ");
        scanf("%s", sendBuff);
        send(clientSocket, sendBuff, sizeof(sendBuff), 0);
        if(strcmp(sendBuff, "Exit") == 0) {
            break;
        }
        strcpy(sendBuff, "");
        int readBytes = recv(clientSocket, recvBuff, sizeof(recvBuff), 0);
        recvBuff[readBytes] = '\0';
        printf("Received from server: %s", recvBuff);
        strcpy(recvBuff, "");
        printf("\n");

    }

    close(clientSocket);


}