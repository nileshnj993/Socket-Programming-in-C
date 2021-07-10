#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>


int main()
{
    int s,r,recb,sntb,x;
    struct sockaddr_in server;
    char buff[50];
    s=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_port=htons(7503);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    r=connect(s,(struct sockaddr*)&server,sizeof(server));
    if(r==-1) {
        printf("\nConnection error.");
        exit(0);
    }
    printf("Enter File Name: ");
    scanf("%s", buff);

    sntb=send(s,buff,sizeof(buff),0);
    recb=recv(s,buff,sizeof(buff),0);
    printf("\n%s\n", buff);
    if(strcmp(buff,"File does not exist!")==0) {
        close(s);
        exit(0);
    }
    int ch=0;
    while(ch!=4)
    {
        printf("\n1.Search\n2.Replace\n3.Reorder\n4.Exit\nEnter your choice: ");
        scanf("%d",&ch);
        buff[0]=ch;
        char str1[50],str2[50];
        int n,i,j;
        switch(ch)
        {
            case 1:
                printf("\nEnter string to be searched: ");
                scanf("%s",str1);
                n=strlen(str1);
                buff[1]=n;
                for(i=0;i<n;i++)
                buff[i+2]=str1[i];
                buff[i+2]='\0';
                sntb=send(s,buff,sizeof(buff),0);
                recb=recv(s,buff,sizeof(buff),0);
                n=buff[0];
                printf("\nWord Count: %d\n",n);
                break;
            case 2:
                printf("\nEnter string to be searched: ");
                scanf("%s",str1);
                n=strlen(str1);
                buff[1]=n;
                for(i=0;i<n;i++)
                    buff[i+2]=str1[i];
                buff[i+2]='\0';
                sntb=send(s,buff,sizeof(buff),0);
                printf("\nEnter replacement string: ");
                scanf("%s",str2);
                n=strlen(str2);
                buff[1]=n;
                i=2;
                for(j=0;j<n;j++) {
                    buff[i]=str2[j];
                    i++;
                }
                buff[i]='\0';
                sntb=send(s,buff,sizeof(buff),0);
                recb=recv(s,buff,sizeof(buff),0);
                printf("%s\n",buff);
                break;
            case 3:
                sntb=send(s,buff,sizeof(buff),0);
                recb=recv(s,buff,sizeof(buff),0);
                printf("%s\n",buff);
                break;
            case 4:
                sntb=send(s,buff,sizeof(buff),0);
                break;
            default:
                printf("\n Try Again!\n");
        }
    }
    close(s);
}