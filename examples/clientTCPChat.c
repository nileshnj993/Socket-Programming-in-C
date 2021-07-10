#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main() {

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(7500);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(server.sin_zero, 0, sizeof(server.sin_zero));

    if (connect(clientSocket, (struct sockaddr*) &server, sizeof(server)) < 0) {
        printf("Can't connect to server");
        exit(0); close(clientSocket);
    } else {
        printf("Connected to server!\n");
    }

    int pid = fork();
    char buff[50];
    while(1) {
        if(pid == 0) { //child sends
            fgets(buff, 50, stdin);
            send(clientSocket, buff, sizeof(buff), 0);
            printf("Sent by child process: %d\n", getpid());
            if(strcmp("bye\n", buff) == 0) {
                printf("Sending process stopped\n");
                break;
            }
            strcpy(buff, "");
        } else { //parent reads
            int bytes = recv(clientSocket, buff, sizeof(buff), 0);
            buff[bytes] = '\0';
            printf("Server: %s", buff);
            printf("Received by parent process: %d\n", getpid());
            if(strcmp("bye\n", buff) == 0) {
                printf("Receiving process stopped \n");
                break;
            }
            strcpy(buff, "");
        }
    }

    close(clientSocket);


}