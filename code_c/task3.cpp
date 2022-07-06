#include<stdio.h>
//task3
int main()
{
	float value[30];
	float total;
	for(int i = 0; i< 30;i++)
	{
		printf("enter value electronic product the day % d: ",i+1);
		scanf("%2f",&value[i]);//part a
		if(value[i]<0){
			printf("enter value electronic product the day% d: ",i+1);
			scanf("%2f",&value[i]);
			i=i-1;
		}
	}
	for(int i = 0;i<30;i++)
	{
		total=total+value[i];//part b
	}
	printf("total number of finished product is: %2f",total);
	for(int i = 0; i<30;i++){
		if(value[i]>=400)
		{
			printf("The day have been target is: %d",i+1);//part c
		}
	}
	printf("Total revenue from selling products is: %2f USD",total*739);//part d
}