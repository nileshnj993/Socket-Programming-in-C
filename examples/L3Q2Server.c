#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

void swap(char *x, char *y) { 
    char temp;  temp = *x;  *x = *y;  *y = temp; 
} 

void permute(char *a, int l, int r) { 
    int i; 
    if (l == r) 
        printf("%s\n", a); 
    else { 
        for (i=l; i<=r; i++) { 
            swap((a+l), (a+i)); 
            permute(a, l+1, r); 
            swap((a+l), (a+i)); 
        } 
    } 
} 

int main() {
    
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server, client;

    memset(&server, 0, sizeof(server));
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(7505);
    
    if(bind(serverSocket, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Bind failed\n");
    } else {
        printf("Bind Successful\n");
    }

    char buff[50];
    while(1) {
        socklen_t len = sizeof(client);
        recvfrom(serverSocket, buff, sizeof(buff), 0, (struct sockaddr *) &client, &len);
        if(strcmp("bye", buff) == 0) {
            break;
        }
        permute(buff, 0, strlen(buff)-1);
        strcpy(buff,"Permutations printed!");
        sendto(serverSocket, buff, sizeof(buff), 0, (struct sockaddr *) &client, sizeof(client));
        strcpy(buff, "");
    }
    close(serverSocket);

}