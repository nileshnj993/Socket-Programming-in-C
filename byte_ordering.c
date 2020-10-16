#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
	int x;
	memset(&x,0,sizeof(x));
	x = 6145;
	int *ptr = &x;
	char c[4]; // 32 bits - 1 address can store 8 bits
	memset(c,0,4);
	memcpy(c,ptr,4); // each index of c has 8 bits in system byte ordering
	for(int i=0;i<sizeof(x);i++){
		printf("%d",c[i]);
		printf("\n");
	}
}

// as LSB is getting printed first, system has Little Endian byte ordering

