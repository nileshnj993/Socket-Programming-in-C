#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

int main(){
int sockfd1 = socket(AF_INET,SOCK_STREAM,0); // AF_INET specifies which type of addressing is being used - AF_INET is IPv4, AF_INET6 is IPv6 etc.
// SOCK_STREAM specifies the type. It says that the protocol used accepts data in this format. SOCK_STREAM is TCP, SOCK_DGRAM is UDP.
// Last parameter is 0 to specify default value for corresponding first 2 parameters.
if(sockfd1==-1){
	printf("Invalid combination of protocol and stream entered\n");
}
else{
	printf("Socket creation successful\n");
}
int sockfd2 = socket(AF_ROUTE,SOCK_STREAM,0);
if(sockfd2==-1){
	printf("Invalid combination of protocol and stream entered\n");
}
else{
	printf("Socket creation successful\n");
}

int clientsocket;
	struct sockaddr_in server_addr;
	socklen_t addr_len; 
	clientsocket = socket(AF_INET,SOCK_STREAM,0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2421); // port number - ephemeral
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // set address of server
	memset(server_addr.sin_zero,'\0',sizeof(server_addr.sin_zero)); // set extra parameter to all zeroes - convention
	addr_len = sizeof(server_addr);
	int connection_status = connect(clientsocket,(struct sockaddr*)&server_addr,addr_len); // returns 0 if successful, -1 if unsuccessful
	if(connection_status==0){
		printf("Connection to server successful!\n");
	}
	else{
		printf("Connection to server unsuccessful!\n");
	}
}