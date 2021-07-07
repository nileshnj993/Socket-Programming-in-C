#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

struct array {
    int size;
    int a[10];
    int option;
    int item;
    int even[5];
    int esize;
    int odd[5];
    int osize;
};

int main(){
	struct array a;
	int port;
	int i,j;

	printf("Enter the port number:");
	scanf("%d",&port);

	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		printf("Socket error creation");
		exit(0);
	}

	struct sockaddr_in server;

	server.sin_family=AF_INET;
	server.sin_port=htons(port);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

	if(connect(sockfd,(struct sockaddr*)&server,sizeof(server))==-1){
		printf("Connection error\n");
		exit(0);
		close(sockfd);
	}

	printf("Socket Connected.\n");

	printf("\nEnter the number of elements:");
	scanf("%d",&a.size);

	printf("Enter the elements:");
	for( i=0;i<a.size;i++){
		scanf("%d",&a.a[i]);
	}

	while(1){
		printf("\nChoose Operation ");
		printf("\n1. Search\t");
		printf("2. Sort in ascending order  ");
		printf("3. Sort in descending order  ");
		printf("4. Split array  ");
		printf("5. Exit\n");

		scanf("%d",&a.option);

		if(a.option==5){
			printf("\nExiting");
			exit(0);
		}

		if(a.option==1){
			printf("\nEnter the element to be searched:");
			scanf("%d",&a.item);
		}
			if(send(sockfd,(struct array*)&a,sizeof(a),0)==-1){
				printf("\nSending error");
				close(sockfd);
				exit(0);
				
			}
		    if(recv(sockfd,(struct array*)&a,sizeof(a),0)==-1){
		    	printf("\nReceiving error");
		    	close(sockfd);
		    	exit(0);
		    }

		 if(a.option==1){
		    if(a.item==1){
		    	printf("\nElement found");

		    }
		    else{
		    	printf("\nelement not found");
		    }
		}
		
		else if(a.option==2){
			printf("\nArray sorted in ascending order is:\n");
			for( i=0;i<a.size;i++){
				printf("%d ",a.a[i]);
			}
		}

		else if(a.option==3){
			printf("\nArray sorted in descending order is:\n");
			for( i=0;i<a.size;i++){
				printf("%d ",a.a[i]);
			}
		}

		else{
			printf("\nThe even array is:\n");
			for( i=0;i<a.esize;i++){
				printf("%d ",a.even[i]);
                
			}

			printf("\nThe odd array is:\n");
			for( i=0;i<a.osize;i++){
				printf("%d ",a.odd[i]);
			}
		}
	}
	print("\n\n");
	close(sockfd);


}