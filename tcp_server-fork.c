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
	if(argc<2){
		error("Too less arguments!");
	}
	if(argc>2){
		error("Too many arguments!");
	}

	int sockfd, newsockfd,n;

	pid_t childpid; // for handling multiple clients using fork

	struct sockaddr_in servaddr, cliaddr;
	socklen_t cli_len;
	char buffer[1024];
	int portno = atoi(argv[1]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0){
		error("Error creating socket!");
	}
	printf("Server socket is created!\n");

	memset(&servaddr, '\0', sizeof(servaddr));
	memset(buffer, '\0', sizeof(buffer));
	memset(&servaddr.sin_zero, '\0', sizeof(servaddr.sin_zero));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(portno);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	if(bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0){
		error("Error in binding!");
	}

	listen(sockfd, 5);
	cli_len = sizeof(cliaddr);
	

	while(1){
		newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &cli_len);
		if(newsockfd<0){
			error("Error on accept!");
		}
		if((childpid=fork())==0){ // successful fork
			close(sockfd); // no need to use parent socket (listening for new connections) when we are in child process
			while(1){
				read(newsockfd, buffer, sizeof(buffer));

				if(strcmp(buffer, "exit")==0){
					printf("Disconnected!\n");
					break;
				}

				else{
					printf("Client: %s\n",buffer);
					memset(buffer, '\0', sizeof(buffer));
					fgets(buffer,sizeof(buffer),stdin);
					write(newsockfd, buffer, strlen(buffer));
					memset(buffer, '\0', sizeof(buffer));
				}
			}
			close(newsockfd);
			exit(0);
		}

		else{
			close(newsockfd);
		}
		
	return 0;
}
}

