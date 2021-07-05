#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

void error(const char *msg){
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[]){
	if(argc<3){
		error("Lesser arguments provided than required!");
	}
	if(argc>3){
		error("Too many arguments!");
	}

	struct sockaddr_in servaddr;
	int portno, sockfd,n;
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0){
		error("Error creating socket!");
	}
	memset(&servaddr, '\0', sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(portno);
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	memset(servaddr.sin_zero,'\0',sizeof(servaddr.sin_zero));

	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))<0){
		error("Connection failed!");
	}
	int num1, num2, choice, ans;
	char buffer[255];
	s:memset(buffer, '\0', sizeof(buffer));
	n = read(sockfd, buffer, sizeof(buffer));
	if(n<0)
		error("Error reading!");
	printf("Server - %s\n",buffer);
	scanf("%d",&num1);
	write(sockfd, &num1, sizeof(int));

	memset(buffer, '\0', sizeof(buffer));
	n = read(sockfd, buffer, sizeof(buffer));
	if(n<0)
		error("Error reading!");
	printf("Server - %s\n",buffer);
	scanf("%d",&num2);
	write(sockfd, &num2, sizeof(int));

	memset(buffer, '\0', sizeof(buffer));
	n = read(sockfd, buffer, sizeof(buffer));
	if(n<0)
		error("Error reading!");
	printf("Server - %s\n",buffer);
	scanf("%d",&choice);
	write(sockfd, &choice, sizeof(int));
	
	memset(buffer, '\0', sizeof(buffer));
	if(choice>5){
		read(sockfd,buffer, sizeof(buffer));
		printf("Server - %s", buffer);
		goto s;
	}
	

	n = read(sockfd, &ans, sizeof(int));
	if(n<0){
		error("Error reading!");
	}
	
	
	if(choice!=5){
		printf("Server - The answer is %d\n",ans);
		goto s;
	}

	q:
		printf("You have exited the program!\n");
		close(sockfd);
	}