#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	struct addrinfo hints, *res;
	bzero(&hints, sizeof(hints) ) ;
	hints.ai_flags = AI_CANONNAME;
	hints.ai_family = AF_INET;
	getaddrinfo("freebsd4", "domain", &hints, &res);
}