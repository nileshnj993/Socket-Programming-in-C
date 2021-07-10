#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server, client;

    server.sin_family = AF_INET;
    server.sin_port = htons(7500);
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
    int connSocket = accept(serverSocket, (struct sockaddr*) &client, &addrLen);
    if (connSocket < 0) {
        printf("Can't accept connection");
        close(serverSocket); exit(0);
    } else {
        printf("Connection Accepted! Start chatting\n");
    }

    int pid = fork();
    char buff[50];

    while(1) {
        if(pid == 0) { //child reads
            int bytes = recv(connSocket, buff, sizeof(buff), 0);
            buff[bytes] = '\0';
            printf("Client: %s", buff);
            printf("Received by child process: %d\n", getpid());
            if(strcmp(buff, "bye\n") == 0) {
                printf("Receiving process stopped\n");
                break;
            }
            strcpy(buff, "");
        } else { //parent sends
            fgets(buff, 50, stdin);
            send(connSocket, buff, sizeof(buff), 0);
            printf("Sent by parent process: %d\n", getpid());
            if(strcmp(buff, "bye\n") == 0) {
                printf("Sending process stopped \n");
                break;
            }
            strcpy(buff, "");
        }
    }

    close(connSocket);
    close(serverSocket);

}