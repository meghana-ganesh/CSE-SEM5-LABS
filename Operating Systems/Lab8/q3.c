#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
void* child_thread( void * param )
{
	int n = (int)param;
	int *arr_prime = (int*)malloc(n*sizeof(int));
	int k = 0;
	for(int i=2;i<n;i++)
	{
		int flag = -1;
		for(int j=2;j<i;j++)
		{
			if(i % j == 0)
				flag = 0;
		} 
		if(flag != 0) 
		{
			flag = 1; 
			arr_prime[k++] = i; 
		}        
	}
	return arr_prime;
}

int main(int argc,char *argv[])
{
	pthread_t thread;
	int n = atoi(argv[1]);
	int *arr_prime1;
	pthread_create(&thread, 0, &child_thread,(void*)n);
	pthread_join(thread,(void**)&arr_prime1);
	for (int i=0;i<n;i++)
	{
		if(arr_prime1[i] != 0)
			printf("%d\n",arr_prime1[i]);
	}
}