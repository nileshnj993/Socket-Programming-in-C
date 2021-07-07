#include<stdio.h>
   #include<unistd.h>
 
   int main()
   {
       pid_t child;
       child = fork();
       printf("%d\n",child);
       return 0;
   }