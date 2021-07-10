#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>


int main() {
    
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server;

    memset(&server, 0, sizeof(server));
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(7505);

    char buff[50];
    while(1) {
        printf("Enter string: ");
        scanf("%s", buff);
        sendto(clientSocket, buff, sizeof(buff), 0, (struct sockaddr *) &server, sizeof(server));
        if(strcmp("bye", buff) == 0) {
            break;
        }
        socklen_t len = sizeof(server);
        recvfrom(clientSocket, buff, sizeof(buff), 0, (struct sockaddr *) &server, &len);
        printf("%s\n", buff);
        strcpy(buff, "");
    }
    close(clientSocket);

}