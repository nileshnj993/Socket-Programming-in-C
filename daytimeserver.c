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
	if(argc<2){
		error("Port number not provided!\n");
	}
	if(argc>2){
		error("Too many arguments provided!\n");
	}

	int portno = atoi(argv[1]);
	struct sockaddr_in servaddr, cliaddr;
	socklen_t clilen;

	int n_client = 0;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	int newsockfd;
	if(sockfd<0){
		error("Error creating socket!\n");
	}
	memset(&servaddr,'\0',sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(portno);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	int status;
	status = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(status<0){
		error("Error in binding!\n");
	}

	listen(sockfd, 10);
	clilen = sizeof(cliaddr);
	while(1){
		n_client++;
		newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
		time_t currentTime;
		time(&currentTime);
		printf("Client %d requested for time at %s\n",n_client,ctime(&currentTime));
		write(newsockfd, ctime(&currentTime),1024);
	}
	return 0;
}
