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
  int sockfd,newsockfd,len,pid,recvmsg,sendmsg;
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd == -1)
  {
	printf("Socket Creation Failure\n");
  }
  else
  {
	printf("Socket Created Successfully\n");
  }
  char buffsend[80] = "";
  char buffrecv[80] = "";
  struct sockaddr_in serveraddr,cliaddr;
  bzero(&serveraddr,sizeof(serveraddr));
  bzero(&cliaddr,sizeof(cliaddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(x);
  serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if((bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr))) == -1)
  {
	printf("Bind Failure\n");
	exit(0);
  }
  else
  {
	printf("Bind Successful\n");
  }
  if((listen(sockfd,5))!=0)
  {
	printf("Listen Failed\n");
	close(sockfd);
	exit(0);
  }
  else
  {
	printf("Listening.....\n");
  }
  len = sizeof(cliaddr);
  newsockfd = accept(sockfd,(struct sockaddr *)&cliaddr,&len);
  if(newsockfd!=0)
  {
	printf("Accepting Failed\n");
  }
  printf("Accepting client.....\n");

  pid = fork();
  if(pid == 0)
  {
  	printf("In Child Process\nPID: %d\nPPID: %d\n",getpid(),getppid());
  }
  else
	printf("In Parent Process\nPID: %d\nPPID: %d\n",getpid(),getppid());

  while(1)
  {
	if(pid == 0) // Child Process
	{
  	// receiving messages 
  	recvmsg = recv(newsockfd,buffrecv,80,0);
  	printf("Sent By Client:%s\n",buffrecv);
  	if(strncmp("exit",buffrecv,4) == 0)
  	{
    	printf("Server Exit\n");
    	break;
  	}
  	bzero(buffrecv,sizeof(buffrecv));
	}
	else // Parent Process
	{
  	// send messages
  	printf("Enter a String to be sent to the client\n");
  	fgets(buffsend,sizeof(buffsend),stdin);
  	sendmsg = send(newsockfd,buffsend,sizeof(buffsend),0);
  	if(strncmp("exit",buffsend,4) == 0)
  	{
    	printf("Exiting Server\n");
    	break;
  	}
	}
  }
  close(newsockfd);
  close(sockfd);
  return 0;
}
