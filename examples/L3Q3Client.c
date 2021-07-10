#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main() {

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(7501);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(server.sin_zero, 0, sizeof(server.sin_zero));

    if (connect(clientSocket, (struct sockaddr*) &server, sizeof(server)) < 0) {
        printf("Can't connect to server");
        exit(0); close(clientSocket);
    } else {
        printf("Connected to server!\n");
    }

    char buff[50];
    int buff1[50], buff2[50];
    printf("Enter alphanumeric string: ");
    scanf("%s", buff);
    send(clientSocket, buff, sizeof(buff), 0);
    int bytes = recv(clientSocket, buff1, sizeof(buff1), 0);
    printf("Received from process: %d\n", buff1[buff1[0]]);
    bytes = recv(clientSocket, buff2, sizeof(buff2), 0);
    printf("Received from process: %d\n", buff2[buff2[0]]);
    
    close(clientSocket);
}