#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(){
	int clientsocket; // descriptor to client socket
	struct sockaddr_in servaddr;
	socklen_t addrlen;
	clientsocket = socket(AF_INET,SOCK_STREAM,0);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(2341);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(servaddr.sin_zero,'\0',sizeof(servaddr.sin_zero));
	int conn_status = connect(clientsocket,(struct sockaddr*)&servaddr,sizeof(servaddr));
	printf("%d",conn_status);
}
