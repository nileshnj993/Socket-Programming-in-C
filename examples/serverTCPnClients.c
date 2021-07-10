#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

int main() {

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server, client;

    server.sin_family = AF_INET;
    server.sin_port = htons(9001);
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

    int clientNo = 0;
    while(1) {
        printf("Server waiting to accept new connection!\n");
        socklen_t addrLen = sizeof(client);
        int connSocket = accept(serverSocket, (struct sockaddr*) &client, &addrLen);
        if (connSocket < 0) {
            printf("Can't accept connection");
            close(serverSocket); exit(0);
        } else {
            printf("Connection Accepted!\n");
            clientNo++;
        }
        int pid = fork();
        if(pid == 0) { //child process to handle client
            close(serverSocket); //child process does not need to listen for connections
            char recvBuff[50];
            while(1) { //handling client
                int readBytes = recv(connSocket, recvBuff, sizeof(recvBuff), 0);
                recvBuff[readBytes] = '\0';
                printf("Message received from client %d: ", clientNo);
                printf("%s", recvBuff);
                printf("\n");
                if(strcmp(recvBuff, "Exit") == 0) {
                    close(connSocket);
                    exit(0); //exit child process
                }
                //echoing same message to client
                send(connSocket, recvBuff, sizeof(recvBuff), 0);
                strcpy(recvBuff, "");
            }
        }

         //parent process
        close(connSocket);
    }

    close(serverSocket);
    


}