#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
	short x;
	x = 280;
	short y = htons(x);
	printf("%d",y);
	printf("\n%d",ntohs(y));
	printf("\n");
	struct in_addr sock_addr;
	sock_addr.s_addr = htons(x);
	printf("%s\n",inet_ntoa(sock_addr));
	inet_aton(inet_ntoa(sock_addr),&sock_addr);
	printf("%d",sock_addr.s_addr);
}