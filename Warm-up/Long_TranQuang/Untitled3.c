#include<stdio.h>
#include<stdlib.h>
int main(){
	char str[100];
	int i;
	for(i=0;i<100;i++){
		str[i++] = (char)(0);
	}
	printf("%d", i);
}
