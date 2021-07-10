#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main() {

    char buff[50];
    fgets(buff, 50, stdin);
    printf("%s", buff);
    printf("%d", strcmp("bye\n", buff));
}