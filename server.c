#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

void error(const char *msg){
	perror(msg); // displays error
	exit(1); // exits program
}

int main(int argc, char *argv[]){ // argc = number of arguments and argv is an array of arguments
	// argv will contain file name and port number as arguments
	// argc = 2
	if(argc<2){
		error("Port number not provided! Program terminated.");
	}
	if(argc>2){
		error("Too many arguments! Program terminated.");
	}
	int sockfd, newsockfd, portno,n;
	// sockfd - socket descriptor that is always listening
	// newsockfd - socket descriptor for each client sending connect request
	
	char buffer[255];
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;
	socklen_t client_length;

	sockfd = socket(AF_INET,SOCK_STREAM,0); // TCP socket
	if(sockfd<0){
		error("Error opening socket!");
	}

	memset(&serveraddr,'\0',sizeof(serveraddr));
	portno = atoi(argv[1]); // command line argument
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(portno);
	serveraddr.sin_addr.s_addr = INADDR_ANY;

	if(bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr))<0){
		error("Binding failed!");
	}

	listen(sockfd,5); // 5 is backlog
	client_length = sizeof(clientaddr);
	newsockfd = accept(sockfd, (struct sockaddr *)&clientaddr, &client_length);
	// this accepts connections from clients of structure address clientaddr and length client_length.
	// We need to pass pointer to length as the value may change while in program depending on how much the kernel allocates.
	if(newsockfd<0){
		error("Error on accept!");
	}

	while(1){
		memset(buffer, '\0',sizeof(buffer)); // clear buffer
		n = read(newsockfd, buffer, sizeof(buffer)); // read from client and stored in buffer
		if(n<0){
			error("Error on reading!");
		}
		printf("Client : %s\n",buffer); // printing message sent by client that is stored in the buffer
		memset(buffer,'\0',sizeof(buffer)); // clear so server can reply now
		fgets(buffer, sizeof(buffer),stdin); // read into buffer from standard input stream
		n = write(newsockfd, buffer, sizeof(buffer)); // take content from data and send to client 
		// can use send(newsockfd,buffer,sizeof(buffer),0) also as well
		if(n<0){
			error("Error on writing!");
		}
		int i = strncmp("Bye",buffer,3); // when buffer contains "Bye" of length 3, it quits
		if(i==0){
			break;
		}
	}
	close(newsockfd);
	close(sockfd);
	return 0;
}
