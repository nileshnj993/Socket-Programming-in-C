#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main()
{
  int x;
  printf("Enter port number: ");
  scanf("%d", &x);
  int sockfd;
  int retval;
  int recvmsg,sendmsg;
  struct sockaddr_in serveraddr;
  char buff[80],buffsend[80];
  bzero(&serveraddr,sizeof(serveraddr));
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd == -1)
  {
	printf("Socket Creation Failure\n");
  }
  else
  {
	printf("Socket Creation Successful\n");
  }
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(x);
  serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  retval = connect(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));

  if(retval == -1)
  {
	printf("Connection Failed\n");
	close(sockfd);
	exit(0);
  }
  else
  {
	printf("Connection Successful\n");
  }
  int pid = fork();
  if(pid == 0)
   	 printf("In Child Process\nPID : %d\nPPID : %d\n", getpid(), getppid());
    else
   	 printf("In Parent Process\nPID : %d\nPPID : %d\n", getpid(), getppid());
  while(1)
  {
	if(pid == 0) // Child Process
	{
  	// receiving messages 
  	recvmsg = recv(sockfd,buff,sizeof(buff),0);
  	printf("Receiving from server: %s\n", buff);
   		 if (strncmp("exit", buff, 4) == 0) {
   			 printf("Client Exit\n");
   			 break;
   		 }
   		 bzero(buff, sizeof(buff));
	}
	else // Parent Process
	{
  	// Sending messages 
  	bzero(buffsend, sizeof(buffsend));
   		 printf("Enter the string to be sent to the client: \n");
   		 fgets(buffsend, sizeof(buffsend), stdin);
   		 sendmsg = send(sockfd, buffsend, sizeof(buffsend), 0);
   		 if (strncmp("exit", buffsend, 4) == 0) {
   			 printf("Client Exiting\n");
   			 break;
   		 }
	}
  }


  return 0;
}
