#include<stdio.h>
//task 2
int main(){
	int n,s;
	printf("Enter number interger n: %d");
	scanf("%d",&n);
	if(n%2==0)
	{
		for(int i = 1;i<=n;i++){
			s=s+i*i;
		}
	}
	else
	{
		for(int i = 1;i<=n;i++){
			s=s+i;
		}
	}
	
}