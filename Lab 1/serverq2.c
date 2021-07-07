#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
	int sockfd,port;
	int clilen; // length of client socket
	printf("Enter port number: ");
	scanf("%d", &port);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[50]; // buffer to exchange data

	sockfd=socket(AF_INET,SOCK_DGRAM,0); // UDP CONNECTION AS D_GRAM
	if(sockfd==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	server.sin_family=AF_INET;
	server.sin_port=htons(port);
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	len=sizeof(client);
	clilen=sizeof(client);

    if(bind(sockfd,(struct sockaddr*)&server,sizeof(server))==-1){
		printf("\nBinding error.");
		exit(0);
	}
	printf("\nSocket binded.\n");

    while(1){

        if(recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,&clilen) ==-1){

		    printf("\nMessage Receiving Failed");		
		    close(sockfd);
		    exit(0);
	}	

	printf("%s\n", buff);
	if(!strcmp(buff,"halt") || !strcmp(buff,"Halt"))
    {
        printf("Shutting down server..");
        close(sockfd);
        break;
    }
		
	
	char buff2[50];
	strcpy(buff2,buff);
	buff[1]=strlen(buff2);
	int n=0;
	for(int i=0;i<buff[1];i++)
		if(buff2[i]=='a'||buff2[i]=='e'||buff2[i]=='o'||buff2[i]=='i'||buff2[i]=='u') // vowel count
			n++;
	buff[2]=n;
	buff[0]=1;
	for(int i=0;i<buff[1]/2;i++) // check palindrome
	{
		if(buff2[i]!=buff2[buff[1]-i-1])
		{
			buff[0]=0;
			break;
		}
	}
	if(sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,len)==-1){
		printf("\nMessage Sending Failed");
		close(sockfd);
		exit(0);
	}
	
	if(!strcmp(buff,"halt") || !strcmp(buff,"Halt"))
		break;

}
	close(sockfd);
}