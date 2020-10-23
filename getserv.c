#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
	struct servent *ptr;
	ptr = getservbyname("ftp","tcp");
	printf("%s\n",ptr->s_name);
	printf("%s\n",ptr->s_proto);
	printf("%d\n",ntohs(ptr->s_port));
}