#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>


int main() {
    int serverSocket, connSocket;

    struct sockaddr_in server;
    struct sockaddr_in client;
    

    //Create server socket
    serverSocket = socket(PF_INET, SOCK_STREAM, 0);

    //Initialize server
    server.sin_family = AF_INET;
    server.sin_port = htons(8000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(server.sin_zero, '\0', sizeof(server.sin_zero));

    //Bind server to socket
    bind(serverSocket, (struct sockaddr *) &server, sizeof(server));

    if(listen(serverSocket, 5) == 0) {
        printf("Listening for connections");
    } else {
        printf("Some error");
    }

    socklen_t addrSize = sizeof(client);
    //Accept connections
    connSocket = accept(serverSocket, (struct sockaddr *) &client, &addrSize);

    //send
    char buffer[1024];
    strcpy(buffer, "Hello World\n");
    send(connSocket, buffer, 13, 0);

    //close
    close(connSocket);
    close(serverSocket);

}