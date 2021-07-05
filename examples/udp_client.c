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
	if(argc<3){
		error("Too less arguments!");
	}
	if(argc>3){
		error("Too many arguments!");
	}

	int port = atoi(argv[2]);
	int sockfd; struct sockaddr_in servaddr;

	char buffer[1024];
	memset(buffer, '\0',sizeof(buffer));
	sockfd = socket(AF_INET, SOCK_DGRAM,0);
	if(sockfd < 0){
		error("Error in creating socket!");
	}

	memset(&servaddr, '\0', sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	fgets(buffer, sizeof(buffer), stdin);
	sendto(sockfd, buffer, sizeof(buffer),0, (struct sockaddr *)&servaddr, sizeof(servaddr));
	printf("Data sent: %s", buffer);
	close(sockfd);

}