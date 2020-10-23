#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
	int af;
	socklen_t clilen;
	struct sockaddr_in6 cli; /* IPv6 struct */
struct hostent *ptr;
af = AF_INET6;
setsockopt(STDIN_FILENO, IPPROTO_IPV6, IPV6_ADDRFORM, &af, sizeof(af));
clilen = sizeof(cli);
getpeername(0, (struct sockaddr *)&cli, &clilen);
printf("%s",inet_ntop(cli.sin6_addr));
ptr = gethostbyaddr(&cli.sin6_addr, 16, AF_INET);
	printf("%s\n",ptr->h_name);
//	printf("%s\n",ptr->h_proto);
	//printf("%d\n",ntohs(ptr->h_port));
}