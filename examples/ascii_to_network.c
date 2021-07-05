#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

void ipv4_test(){
	char addr[100]; // to store IP address in dotted decimal format
	struct in_addr sock_addr; // stores network address in network byte format.
	strcpy(addr,"127.1.2.3");
	// sock_addr = inet_addr(addr);
	// printf("%d\n",sock_addr);
	// memset(addr,0,sizeof(addr));
	if(inet_aton(addr,&sock_addr)){ // if it returns 1(true) then the conversion is successful
		printf("%d\n",sock_addr.s_addr); // sock_addr is a structure object, s_addr is the unsigned integer variable that stores the numerical equivalent of the ip address
	}
	memset(addr,0,sizeof(addr));
	char *addr_final;
	addr_final = inet_ntoa(sock_addr); // numeric to dotted decimal
	printf("%s\n",addr_final);
}

void ipv6_test(){ // ALL FUNCTIONS WORK WITH IPv4 ALSO
	char addr[100]; 
	struct in_addr sockaddr;
	strcpy(addr,"2001:0db8:85a3:0000:0000:8a2e:0370:7334"); // stored separated by : 16*8 bits
	int x = inet_pton(AF_INET6,addr,(void *)&sockaddr); // Family(AF_INET/AF_INET6), dotted decimal, pointer to structure
	if(x==1){
		printf("%ld\n",(long int)sockaddr.s_addr); // long int needed for IPv6
	}
	char addr_final[INET6_ADDRSTRLEN];
	inet_ntop(AF_INET6,(void *)&sockaddr,addr_final,INET6_ADDRSTRLEN); // pointer to structure, str to store address in, length of destination (predefined) - same without 6 for IPv4
	printf("%s\n",addr_final);
}
int main(){
	ipv4_test();
	ipv6_test();
}