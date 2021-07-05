#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

void error(const char *msg){
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[]){
	if(argc<3){
		error("Too less arguments!");
	}
	if(argc>3){
		error("Too many arguments!");
	}

	int sockfd;
	struct sockaddr_in servaddr;
	int portno = atoi(argv[2]);
	char buffer[1024];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0){
		error("Error in creating socket!");
	}
	printf("Client socket is created!\n");

	memset(&servaddr, '\0', sizeof(servaddr));
	memset(buffer, '\0', sizeof(buffer));
	memset(&servaddr.sin_zero, '\0', sizeof(servaddr.sin_zero));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(portno);
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	

	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))<0){
		error("Error in connection!");
	}
	printf("Connected to Server!\n");
	int n;
	while(1){ // loop till client wants to disconnect
		printf("Client: \t");
		fgets(buffer,sizeof(buffer),stdin);
		n = write(sockfd, buffer, strlen(buffer));
		if(n<0){
			error("Error while writing to Server!");
		}
		if(strcmp(buffer, "exit")==0){
			printf("Disconnected from Server!");
			exit(1);
		}
		memset(buffer, '\0', sizeof(buffer));
		n = read(sockfd, buffer, sizeof(buffer));
		if(n<0){
			error("Error while reading from Server");
		}
		printf("Server: \t%s\n", buffer);
	}


	return 0;
}