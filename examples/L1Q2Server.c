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

    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server, client;

    server.sin_family = AF_INET;
    server.sin_port = htons(8002);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(server.sin_zero, 0, sizeof(server.sin_zero));

    if (bind(serverSocket, (struct sockaddr*) &server, sizeof(server)) < 0) {
        printf("Bind failed");
        close(serverSocket); exit(0);
    } else {
        printf("Bind successful\n");
    }

    

    struct message data;
    char recvBuff[50];
    while(1) {
        socklen_t len = sizeof(client);
        int readBytes = recvfrom(serverSocket, recvBuff, sizeof(recvBuff), 0, (struct sockaddr *) &client, &len);
        printf("Received from client: %s", recvBuff);
        if(strcmp(recvBuff, "Halt") == 0) {
            break;
        }
        int l=0; 
        int r=strlen(recvBuff) - 1; 
        data.palindrome = 1;
        while (r>l) { 
        if (recvBuff[l++] != recvBuff[r--]) { 
            data.palindrome = 0;  
            } 
        } 
        int i; 
        data.a = 0; data.e = 0; data.i = 0; data.o = 0; data.u = 0;
        for(i=0; i<strlen(recvBuff); i++) {
            if(recvBuff[i] == 'a') data.a++;
            if(recvBuff[i] == 'e') data.e++;
            if(recvBuff[i] == 'i') data.i++;
            if(recvBuff[i] == 'o') data.o++;
            if(recvBuff[i] == 'u') data.u++;
            data.string[i] = recvBuff[i];
        }
        data.string[strlen(recvBuff)] = '\0';
        data.size = strlen(recvBuff);
        
        strcpy(recvBuff, "");
        printf("\n");

        sendto(serverSocket, (struct message *) &data, sizeof(data), 0, (struct sockaddr *) &client, sizeof(client));
    }
    close(serverSocket);
}