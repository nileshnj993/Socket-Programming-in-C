#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

void error(const char *msg){
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[]){
	if(argc<2){
		error("Port number not provided!");
	}
	if(argc>2){
		error("Too many arguments provided!");
	}

	struct sockaddr_in servaddr;
	struct sockaddr_in cliaddr;
	socklen_t cli_length;
	int sockfd,newsockfd;
	int portno,n;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0){
		error("Error creating socket!");
	}

	portno = atoi(argv[1]);
	memset(&servaddr,'\0',sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(portno);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	if(bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0){
		error("Binding failed!");
	}

	listen(sockfd,5); // 5 is backlog
	cli_length = sizeof(cliaddr);
	newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &cli_length);
	if(newsockfd<0){
		error("Error on accept!");
	}

	int num1, num2, ans, choice;
	s:n = write(newsockfd, "Enter number 1 : ", strlen("Enter number 1 : "));
	if(n<0){
		error("Error writing to socket");
	}
	
	read(newsockfd,&num1,sizeof(int)); // store integer in num1 that the client enters
	printf("Client - Number 1 is : %d\n",num1);
	n = write(newsockfd, "Enter number 2 : ", strlen("Enter number 2 : "));
	if(n<0){
		error("Error writing to socket");
	}
	read(newsockfd,&num2,sizeof(int)); // store integer in num1 that the client enters
	printf("Client - Number 2 is : %d\n",num2);

	n = write(newsockfd, "Enter your choice:\n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n5.Exit\n", strlen("Enter your choice:\n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n5.Exit\n"));
	if(n<0){
		error("Error writing to socket");
	}
	read(newsockfd, &choice, sizeof(int));
	printf("Client - choice is : %d\n",choice);

	if(choice == 1){
		ans = num1 + num2;
	}
	else if(choice == 2){
		ans = num1 - num2;
	}
	else if(choice == 3){
		ans = num1 * num2;
	}
	else if(choice == 4){
		ans = num1 / num2;
	}
	else if(choice == 5){
		goto q;
	}
	else{
		write(newsockfd, "Invalid choice! Try again!\n", sizeof("Invalid choice! Try again!\n"));
		goto s;
	}

	
	if(choice!=5){
		write(newsockfd, &ans, sizeof(int));
		printf("\n");
		goto s;
	}

	q:
	printf("Execution complete!\n");
	close(newsockfd);
	close(sockfd);
}