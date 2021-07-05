#include "unp.h"
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
	sockfd = Socket(AF_INET,SOCK_STREAM,0);
	if(isfdtype(sockfd,S_IFSOCK)){
		printf("Yes it is a socket descriptor");
	}
	else{
		printf("No, it is not a socket descriptor");
	}
}