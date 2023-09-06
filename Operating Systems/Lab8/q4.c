#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define size 7

void* even_thread(void *param)
{
	int* arr1 = (int*)param;
	int sum = 0;
	for(int i=0;i<size;i++)
	{
		if(arr1[i] % 2 == 0)
			sum += arr1[i];
	}
	return sum;
}

void* odd_thread(void *param)
{
	int* arr2 = (int*)param;
	int sum1 = 0;
	for(int i=0;i<size;i++)
	{
		if(arr2[i] % 2 != 0)
			sum1 += arr2[i];
	}
	return sum1;
}

int main()
{
	pthread_t thread1;
	pthread_t thread2;
	int arr[size] = {0,1,2,3,4,5,6};
	//0+2+4+6=12
	//1+3+5 = 9
	int even_sum = 0,odd_sum = 0;
	pthread_create(&thread1,0,&even_thread,(void*)arr);
	pthread_create(&thread2,0,&odd_thread,(void*)arr);
	pthread_join(thread1,(void*)&even_sum);
	pthread_join(thread2,(void*)&odd_sum);
	printf("\neven sum:%d,odd sum:%d",even_sum,odd_sum);
}