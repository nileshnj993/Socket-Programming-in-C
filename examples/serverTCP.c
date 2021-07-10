#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main() {

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0), connSocket;
    struct sockaddr_in server, client;

    server.sin_family = AF_INET;
    server.sin_port = htons(8001);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(server.sin_zero, 0, sizeof(server.sin_zero));

    if (bind(serverSocket, (struct sockaddr*) &server, sizeof(server)) < 0) {
        printf("Bind failed");
        close(serverSocket); exit(0);
    } else {
        printf("Bind successful\n");
    }
    
    if (listen(serverSocket, 5) < 0) {
        printf("Listening error"); 
        close(serverSocket); exit(0);
    } else {
        printf("Server Listening.....\n");
    }

    socklen_t addrLen = sizeof(client);
    connSocket = accept(serverSocket, (struct sockaddr*) &client, &addrLen);
    if (connSocket < 0) {
        printf("Can't accept connection");
        close(serverSocket); exit(0);
    } else {
        printf("Connection Accepted!\n");
    }

    char sendBuff[50];
    char recvBuff[50];
    while(1) {
        int readBytes = recv(connSocket, recvBuff, sizeof(recvBuff), 0);
        recvBuff[readBytes] = '\0';
        printf("Received from client: %s", recvBuff);
        if(strcmp(recvBuff, "Exit") == 0) {
            break;
        }
        strcpy(recvBuff, "");

        printf("\n");

        printf("Enter message: ");
        scanf("%s", sendBuff);
        send(connSocket, sendBuff, sizeof(sendBuff), 0);
        strcpy(sendBuff, "");

    }

    close(connSocket);
    close(serverSocket);


}