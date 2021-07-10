#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>


int main() {

    int clientSocket;
    struct sockaddr_in server;

    //create client socket
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    //Initialize server
    server.sin_family = AF_INET;
    server.sin_port = htons(8000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(server.sin_zero, '\0', sizeof(server.sin_zero));

    //connect to server
    connect(clientSocket, (struct sockaddr *) &server, sizeof(server));

    //recieve
    char buffer[1024];
    recv(clientSocket, buffer, 1024, 0);
    printf("Data Received: %s", buffer);
    
    close(clientSocket);

}
