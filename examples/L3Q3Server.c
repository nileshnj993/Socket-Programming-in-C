#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>


int compare (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int compare1 (const void * a, const void * b) {
   return ( *(int*)b - *(int*)a );
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server, client;

    server.sin_family = AF_INET;
    server.sin_port = htons(7501);
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
        printf("Connection Accepted!\n");
    }

    
    char buff[50];
    
    int bytes = recv(connSocket, buff, sizeof(buff), 0);
    buff[bytes] = '\0';
    printf("Received String: %s\n", buff);
    int pid = fork();
    int t = 1;
    while(t--) {
        if(pid == 0) { //child
            int num[50], n=1, i;
            for(i=0; i<strlen(buff); i++) {
                if(buff[i]>='0' && buff[i]<='9') {
                    num[n++] = buff[i] - 48;
                }
            }
            qsort(num, n, sizeof(int), compare);
            num[0] = n;
            printf("Sorted numbers: ");
            for(i=1; i<n; i++) {
                printf("%d ", num[i]);
            } printf("\n");
            num[n] = getpid();
            send(connSocket, num, sizeof(num), 0);
            close(connSocket);
            close(serverSocket);
        } else { //parent
            int chars[50], n=1, i;
            
            for(i=0; i<strlen(buff); i++) {
                if(buff[i]>='a' && buff[i]<='z') {
                    chars[n++] = buff[i];
                }
            }
            chars[0] = n;
            qsort(chars, n, sizeof(int), compare1);
            printf("Sorted characters: ");
            for(i=0; i<=n; i++) {
                printf("%c ", (char)chars[i]);
            } printf("\n");
            chars[0] = n;
            chars[n] = getpid();
            send(connSocket, chars, sizeof(chars), 0);
            break;
        }
    }
    close(connSocket);
    close(serverSocket);
}