#include<stdio.h>
int main(){
	int a[5]={0,1,2,3,4};
	int *p1 = &a[1];
	int *p2 = &a[3];
	*(p1-1)=*p2-1;
	*(p2-2)=4;
	*(p1+1)=*p2+2;
	p1++;
	*(p1+1)=*p2+1;
	*(p2+1)=*p1;
	for(int i=0; i<5;i++){
		printf("%d ",a[i]);
	}
}