#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

void error(char *msg){
	perror(msg);
	exit(1);
}

// command line arguments are file name, server IP address and port number(must be same as that of server)
int main(int argc, char *argv[]){
	int sockfd, portno, n;
	struct sockaddr_in servaddr;
	char buffer[255];

	if(argc<3){
		error("Lesser arguments than required!");
	}
	if(argc>3){
		error("Too many arguments!");
	}

	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	if(sockfd<0){
		error("Error opening socket!");
	}

	memset(&servaddr, '\0',sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(portno);
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	memset(servaddr.sin_zero, '\0',sizeof(servaddr.sin_zero));

	if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0){
		error("Connection Failed!");
	}

	while(1){
		memset(buffer,'\0',sizeof(buffer));
		fgets(buffer,sizeof(buffer),stdin);
		n = write(sockfd, buffer, strlen(buffer));
		if(n<0){
			error("Error on writing!");
		}
		memset(buffer,'\0',sizeof(buffer));
		n = read(sockfd, buffer, sizeof(buffer));
		if(n<0){
			error("Error on reading!");
		}
		printf("Server: %s",buffer);
		int i = strncmp("Bye",buffer,3); // when buffer contains "Bye" of length 3, it quits
		if(i==0){
			break;
		}
	}
	close(sockfd);
	return 0;


}