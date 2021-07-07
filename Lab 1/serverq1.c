#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

struct array {
    int size;
    int a[10];
    int option;
    int item;
    int even[5];
    int esize;
    int odd[5];
    int osize;
};

int main() {
    struct array a; //struct with array information to be sent to client

    int sockfd,port, newsockfd;
    int i,j;

    printf("Enter port number: "); //port number for communication
    scanf("%d", &port);

    socklen_t len;
    struct sockaddr_in server, client;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); //socket creation

    if (sockfd == -1) {
	    printf("\nSocket creation error.");
        exit(0);
    }


printf("\nSocket created.");

server.sin_family = AF_INET;
server.sin_port = htons(port);
server.sin_addr.s_addr = htonl(INADDR_ANY);
len = sizeof(client);

if(bind(sockfd, (struct sockaddr*) &server, sizeof(server))==-1){ //socket binding
    printf("\nBinding error.");
    exit(0);
    }

printf("\nSocket binded.");

if(listen(sockfd, 5) ==-1){

    close(sockfd);
    exit(0);
}

printf("\nSocket listening.");
newsockfd = accept(sockfd, (struct sockaddr*)&client, &len); //server accepting socket
if (newsockfd == -1) {
    close(sockfd);
    exit(0);
}

while(1) {

if(recv(newsockfd, (struct array*)&a, sizeof(a), 0)==-1){ //server receiving

    printf("\nMessage receiving failed.");

    close(sockfd);
    close(newsockfd);
    exit(0);
}


if (a.option == 5) { //exit
    printf("\nExiting.");
    break;
}


if (a.option == 1) { // search
    printf("\nSearching for the element."); //linear search
    int found = 0;

    for ( i = 0; i < a.size; i++){
        if (a.a[i] == a.item) {
            found = 1;
        break;
   }
}

    if (found) 
        a.item = 1;
    else 
        a.item = 0;
}

else if (a.option == 2) { // sorting in ascending order
    printf("\nSorting the array in ascending order.");
    for ( i = 0; i < a.size -1; i++) {
        for ( j = 0; j < a.size - i -1; j++) {
            if (a.a[j] > a.a[j + 1]) {
                    int temp = a.a[j];
                    a.a[j] = a.a[j + 1];
                    a.a[j + 1] = temp;
            }
        }
    }
} 

else if (a.option == 3) { // sorting in descending order
    printf("\nSorting the array in descending order.");
    for ( i = 0; i < a.size -1; i++) {
        for ( j = 0; j < a.size - i -1; j++) {
            if (a.a[j] < a.a[j+1]) {
                int temp = a.a[j];
                a.a[j] = a.a[j+1];
                a.a[j+1] = temp;
            }
        }
    }
}

else if (a.option == 4) { //splitting into odd and even
    printf("\nSpliting into odd even sets.");
    a.esize = 0;
    a.osize = 0;
    for ( i = 0; i < a.size; i++) {
        if (a.a[i] % 2 == 0) 
	        a.even[a.esize++] = a.a[i];
        else 
	        a.odd[a.osize++] = a.a[i];
    }
}

printf("\n\n");
if(send(newsockfd, (struct array*)&a, sizeof(a), 0)==-1){ //sending output to client

    printf("\nMessage sending failed.");
    close(sockfd);
    close(newsockfd);
    exit(0);
}
}
printf("\n\n");
close(newsockfd);
close(sockfd);
}