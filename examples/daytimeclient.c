#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>

// RETURNS CURRENT DATE AND TIME TO CLIENT 

void error(const char *msg){
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[]){
	if(argc>3){
		error("Too many arguments provided!\n");
	}
	if(argc<3){
		error("Too less arguments provided!\n");
	}
	int sockfd;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in servaddr;
	memset(&servaddr, '\0',sizeof(servaddr));
	char response[50];
	memset(response, '\0', sizeof(response));
	int portno = atoi(argv[2]);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(portno);
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);

	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	read(sockfd, response, sizeof(response));
	printf("Date and Time from Server : %s\n",response);
	return 0;
}