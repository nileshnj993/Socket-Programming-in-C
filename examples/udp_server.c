#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void error(const char *msg){
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[]){
	if(argc<2){
		error("Port number not provided!");
	}
	if(argc>2){
		error("Too many arguments!");
	}

	int portno = atoi(argv[1]);
	int sockfd, newsockfd;
	struct sockaddr_in servaddr, cliaddr;
	socklen_t cli_len;
	char buffer[1024];

	sockfd = socket(AF_INET, SOCK_DGRAM, 0); // SOCK_DGRAM for UDP
	memset(&servaddr, '\0',sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(portno);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	memset(&servaddr.sin_zero, '\0', sizeof(servaddr.sin_zero));

	if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))<0){
		error("Error in binding!");
	}
	// IN UDP, SERVER DOESN'T LISTEN AND CONNECT. JUST DIRECT RECEIVE. (CONNECTIONLESS PROTOCOL).
	cli_len = sizeof(cliaddr);
	recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&cliaddr, &cli_len);
	printf("Data received: %s", buffer);
}