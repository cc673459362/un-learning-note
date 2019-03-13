#include<stdio.h>

void prib(int *b,int length){
	for(int i=0;i<length;i++){
		printf("b[%d]=%d\t",i,b[i]);
	}
}
int main(){
	int a=10;
	int *b=(int*)malloc(sizeof(int)*10);
	for(int i=0;i<10;i++){
		b[i]=i+1;
	}
	printf("a=%d\n",a);
	prib(b,10);
	free(b);
	
}
